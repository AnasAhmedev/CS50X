import csv
import sys


def main():

    if (len(sys.argv) != 3):
        print("Usage dna.py")
        return

    rows = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)

    with open(sys.argv[2]) as file:
        sequence = file.read()

    subsequences = list(rows[0].keys())[1:]

    result = {}
    for subsequence in subsequences:
        result[subsequence] = longest_match(sequence, subsequence)

    for i in rows:
        match = 0
        for subsequence in subsequences:
            if int(i[subsequence]) == result[subsequence]:
                match += 1
        if match == len(subsequences):
            print(i["name"])
            return
    print("No match")


def longest_match(sequence, subsequence):

    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):

        count = 0

        while True:

            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1

            else:
                break

        longest_run = max(longest_run, count)

    return longest_run


main()
