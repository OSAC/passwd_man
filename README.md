passwd_man
==========

A baby password manager in cui.

It just uses very premitive encryption algorithm(caser cipher) to encrypt the password.
It appends the encrypted password to its executable and hence is standalone an portable arround linux
When you extract password it places the password in clipboard for short period
with in which you are required to past on login field.

-> Compile the program with make
-> initialize the program with switch -i. Provied Master password when asked for.
    ./passwdman -i
-> Store password with switch -s
    ./passwdman -s <site>
-> Get password with switch -g
    ./passwdman -g <site>
    
BUG
---
Don't initialize twice, which shows undetermined behaviours
