# Bank System (C++ OOP)

A console-based bank management system in C++, built with Object-Oriented Programming and text files for data storage. Part of an OOP learning, covering inheritance, encapsulation, and file handling.

## Features

- **Login system** with password encryption and 3 failed-attempt lockout
- **Client management**: list, add, delete, update, and find clients
- **Transactions**: deposit, withdraw, transfer (with transfer log)
- **Total Balances** report
- **User management**: list, add, delete, update, and find system users
- **Role-based permissions** (bitmask permissions per user)
- **Login Register** audit log of all logins
- **Data persistence** through plain text files

## Project Structure

```
BankSystem/
├── MainScreen.cpp            # Entry point
├── Core/                     # Core business logic
│   ├── clsBankClient.h
│   ├── clsUser.h
│   └── clsGlobal.h
├── Lib/                      # Reusable utility libraries
│   ├── clsString.h
│   ├── clsDate.h
│   ├── clsInputValidate.h
│   └── clsUtil.h
├── Screen/                   # UI / screens
│   ├── clsScreen.h
│   ├── clsLoginScreen.h
│   ├── clsMainScreen.h
│   └── ... (client, user, transaction screens)
└── *.txt                     # Data files (clients, users, logs)
```

## Build & Run

From the project root directory:

```bash
g++ MainScreen.cpp -o BankSystem
./BankSystem
```

## Default Login

| Username | Password |
|----------|----------|
| Admin    | 1234     |

Passwords are stored obfuscated in `Users.txt` (simple encryption utility in `Lib/clsUtil.h`).

## Permissions

Each user has a permissions value (bitmask). `-1` grants full (all) access. Permissions are checked before showing management screens.

## NOTES

> This is an educational project demonstrating OOP concepts. It uses text-file storage and simple encryption of data.
> The screen-clearing command (`clear`) is Linux/macOS specific. On Windows, change `system("clear")` to `system("cls")` in the `Screen/` headers.

## TODO
- [ ] Fix the clear screen to work on windows
