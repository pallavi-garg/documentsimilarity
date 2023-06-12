import random
import string

first = []
second = []

def generate_random_word(length):
    characters = string.ascii_letters + string.digits + " "
    return ''.join(random.choice(characters) for _ in range(length))

word_count = 1000000 # Number of words to generate

f = open("set2.txt", "w")
for _ in range(word_count):
    word_length = random.randint(8, 20)  # Generate random word length between 1 and 20
    random_word = generate_random_word(word_length)
    first.append(random_word)
    f.write(random_word + "\n")
f.close()

f = open("set1.txt", "w")
for _ in range(word_count):
    word_length = random.randint(1, 20)  # Generate random word length between 1 and 20
    random_word = generate_random_word(word_length)
    second.append(random_word)
    f.write(random_word + "\n")
f.close()

new_name = 3

counter = 100000
index = 0
print(index, counter)

while index < word_count:
    first[index] = second[index]
    counter -= 1
    index += 1
    if counter == 0:
        f = open(f"set{new_name}.txt", "w")
        for w in first:
            f.write(w + "\n")
        f.close()
        counter = 100000
        new_name +=1

    