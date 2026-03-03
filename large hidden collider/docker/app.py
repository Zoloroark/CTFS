import hashlib
users = {"test":{"password":"password123", "passwordHash":"482c811da5d5b4bc6d497ffa98491e38"}}
def createAccount():
    username = input("Pick a unique username: ")
    if username in users:
        print("User exists, pick another username")
        return
    password = input("Choose a unique password: ")
    passwordHash = hashlib.md5(password.encode()).hexdigest()
    passwordDict = {"password":password, "passwordHash":passwordHash}
    users[username] = passwordDict
def login():
    usernameLogin = input("Enter account username: ")
    passwordLogin = input("Enter password: ")
    passwordHashLogin = hashlib.md5(passwordLogin.encode()).hexdigest()
    if usernameLogin not in users:
        print("That account does not exist")
        return
    if users[usernameLogin]["passwordHash"] == passwordHashLogin:
        if users[usernameLogin]["password"] == passwordLogin:
            print("functionality tbd")
        else:
            print("How did you even get here? I thought md5 was unbreakable")
            with open("flag.txt") as flag:
                print(flag.read())
    else:
        print("wrong password")
        
def main():
    running = True
    while running:
        print("Please choose a selection \n1. Create Account\n2. Login\n3. Quit")
        match input():
            case "1":
                createAccount()
            case "2":
                login()
            case "3":
                running = False
            case _:
                print("Please choose an option")
main()
