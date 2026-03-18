import subprocess
import random
import sys
from faker import Faker

RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
RESET = "\033[0m"

def insert_cmd(name: str, age: int, rg: str, cpf: str):

    cmd = [
        "./bytebase",
        "INSERT",
        "-name", name,
        "-age", str(age),
        "-rg", rg,
        "-cpf", cpf
    ]

    subprocess.run(
        cmd,
        cwd="output/bin",
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL
    )


def generate_data(names: list, ages: list, rgs: list, cpfs: list):

    for _ in range(10000):
        names.append(fake.first_name())
        ages.append(random.randint(19, 79))
        rgs.append(f"{random.randint(10000000,99999999)}-{random.randint(0,9)}")
        cpfs.append(fake.cpf())


if __name__ == "__main__":

    try:

        fake = Faker('pt_BR')

        names = []
        ages = []
        rgs = []
        cpfs = []

        generate_data(names, ages, rgs, cpfs)

        total = len(names)

        print(f"{YELLOW} [INFO] starting users injection on the database... {RESET}")

        for i, (name, age, rg, cpf) in enumerate(zip(names, ages, rgs, cpfs), start=1):

            insert_cmd(name, age, rg, cpf)

            progress = (i / total) * 100
            sys.stdout.write(f"\rprogress: {i}/{total} ({progress:.2f}%)")
            sys.stdout.flush()

        print()

        print(f"{GREEN} [OK] injection done. {RESET}")

    except FileNotFoundError:
        print(f"{RED} [ERROR] no such file of 'output/bin/bytebase'. {RESET}")