import subprocess
import random
import sys
from faker import Faker


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

        for i, (name, age, rg, cpf) in enumerate(zip(names, ages, rgs, cpfs), start=1):

            insert_cmd(name, age, rg, cpf)

            progress = (i / total) * 100
            sys.stdout.write(f"\rProgress: {i}/{total} ({progress:.2f}%)")
            sys.stdout.flush()

        print()

    except Exception as error:
        print(f"{error}")