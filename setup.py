import os
from sys import argv

def main(day):
    # day = input("Enter the day number: ")
    print(f"You selected day {day}")
    os.makedirs(f"day{day}", exist_ok=True)
    open(f"day{day}/test.txt", "w").close()
    with open("template/main.cpp", "r") as template_file:
        content = template_file.read()
        content = content.replace("TAG", f"day{day}")
        content += f'\n// cmake --build . && ./day{day}.out\n'
        with open(f"day{day}/main.cpp", "w") as output_file:
            output_file.write(content)

if __name__ == "__main__":
    main(argv[1])
