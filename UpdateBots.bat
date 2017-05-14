@Echo off
cls
PowerShell -NoProfile -ExecutionPolicy Bypass -Command "& 'C:\crobots\UpdateBots.ps1'"

crobots-win32 -m1000 git-tibbe.r git-dude.r >Match-tibbeVSdude.txt
crobots-win32 -m1000 git-janne.r git-tibbe.r >Match-janneVStibbe.txt
crobots-win32 -m1000 git-dude.r git-janne.r >Match-dudeVSjanne.txt
crobots-win32 -m1000 git-tibbe.r git-dude.r git-janne.r >Match-tibbeVSdudeVSjanne.txt

