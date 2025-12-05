import os

def main():
    day = input("Enter the day number: ")
    print(f"You selected day {day}")
    os.makedirs(f"tag{day}", exist_ok=True)
    open(f"tag{day}/test.txt", "w").close()
    open(f"tag{day}/input.txt", "w").close()
    with open("template/main.cpp", "r") as template_file:
        content = template_file.read()
        content = content.replace("TAG", f"tag{day}")
        content += f'\n// cmake --build . && ./tag{day}.out\n'
        with open(f"tag{day}/main.cpp", "w") as output_file:
            output_file.write(content)

if __name__ == "__main__":
    main()
