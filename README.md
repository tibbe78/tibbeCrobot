# tibbeCrobot 
Tibbes Crobot 
Created for the old CROBOTS game. 
CROBOTS ("see-robots") is a game based on computer programming...
[crobots.deepthought.it](http://crobots.deepthought.it/home.php)

### [tibbeCrobot.r](https://github.com/tibbe78/tibbeCrobot/blob/master/tibbeCrobot.r)
obfuscated version av tibbeCrobot.c same shit different package as tibbeCrobot.c
Tävla mot denna för att inte fuska. :)

### [tibbeCrobot.c](https://github.com/tibbe78/tibbeCrobot/blob/master/tibbeCrobot.c)
full version av min bot med kommentarer osv. .c för att det är typ c kod och det är enklare för editors (notepad++) att veta det.

### [UpdateBots.bat](https://github.com/tibbe78/tibbeCrobot/blob/master/UpdateBots.bat)
UpdateBots.bat kör matcher automatiskt med de filer som powershell updatebots.ps1 hämtade.

### [UpdateBots.ps1](https://github.com/tibbe78/tibbeCrobot/blob/master/UpdateBots.ps1)
UpdateBots.ps1 hämtar de senaste versionerna av bottar från github och sparar lokalt.

### [obfuscate.bat](https://github.com/tibbe78/tibbeCrobot/blob/master/obfuscate.bat)
obfuscate.bat gör din bot oläsbar, men fortfarande fungerande. 
PS. if else satser kan inte bara vara på nya rader. 
#### EJ OK:
```C 
if (true)
  kommando
else
  kommando
``` 

#### OK med mellanslag 
```C
if (true) kommando
else kommando
```

#### OK med {}
```C
if (true) {
  kommando
}
else { 
  kommando
}
```

