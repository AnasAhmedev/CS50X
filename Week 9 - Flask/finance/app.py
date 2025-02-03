import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

app = Flask(__name__)

app.jinja_env.filters["usd"] = usd

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares>0", session["user_id"])

    total_cost = cash

    for stock in stocks:
        stock_data = lookup(stock["symbol"])
        stock["price"] = stock_data["price"]
        stock["total"] = stock["price"] * stock["total_shares"]
        total_cost += stock["total"]

    return render_template("index.html", stocks=stocks, cash=usd(cash), total_cost=usd(total_cost))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Missing symbol")

        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Invalid shares")

        lookedup = lookup(symbol)

        if lookedup is None:
            return apology("Invalid symbol", 400)

        remaining_cash = 0
        price = lookedup["price"]
        cost = price * int(shares)

        user_cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                               user_id=session["user_id"])[0]["cash"]

        if user_cash < cost:
            return apology("Insignificant balance")

        remaining_cash = user_cash - cost

        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?",
                   remaining_cash, session["user_id"])

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, datetime('now'))",
                   session["user_id"], symbol, shares, price)

        return redirect("/history")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute(
        "SELECT * FROM transactions WHERE user_id = ? ORDER BY transacted DESC", session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    session.clear()

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 403)

        elif not request.form.get("password"):
            return apology("must provide password", 403)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    session.clear()

    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Please enter a qoute", 400)

        lookedup = lookup(symbol)

        if lookedup == None:
            return apology("No stock found", 400)

        return render_template("quoted.html", name=lookedup["name"], price=usd(lookedup["price"]), symbol=(lookedup["symbol"]).upper())

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username or not password or not confirmation:
            return apology("Enter a username or password", 400)

        if password != confirmation:
            return apology("Password doesn't match")

        hash = generate_password_hash(password)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        except:
            return apology("Username is already taken", 400)

        return redirect("/login")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares>0", session["user_id"])

    if request.method == "POST":

        shares = request.form.get("shares")
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Symbol is missing", 400)

        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Invalid number of shares", 400)

        shares = int(shares)

        stocks_owned = db.execute(
            "SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", session["user_id"], symbol)

        if not stocks_owned or stocks_owned[0]["total_shares"] < shares:
            return apology("Not enough shares", 400)

        stock_data = lookup(symbol)

        if not stock_data:
            return apology("Invalid symbol", 400)

        price_per_share = stock_data["price"]

        total_sale_value = price_per_share * shares

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                   total_sale_value, session["user_id"])

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, datetime('now'))",
                   session["user_id"], symbol, -shares, price_per_share)

        return redirect("/")

    return render_template("sell.html", stocks=stocks)
