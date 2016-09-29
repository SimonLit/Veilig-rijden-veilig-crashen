# VeiligRijdenVeiligCrashen

Stap 1: Installeer Git op je machine 
Stap 2: Gebruik de command #cd om te gaan de directory waar je de repository files wilt hebben
Stap 3: Voer de volgende command uit om het project te clonen op jouw computer.
        #// git clone https://github.com/SimonLit/VeiligRijdenVeiligCrashen.git
        
Nu heb je alle bestanden van het project op je computer staan, klaar om erin te werken. Maar niet zo snel, eerst een paar essentiele commands.

#// git pull

Git pull kijkt in de repository en gaat na of jij alle bestanden en veranderingen op jouw computer hebt staan. Indien niet zullen deze bestanden en veranderingen gedownload worden. Het is verstandig om regelmatig te pullen als je aan het werken bent aan het project. Zodat je altijd in de meest up to date bestanden aan het werken bent. Dit helpt verkomen van merge conflicten en het maken van dubble code. Indien je een pull doet en je krijgt het bericht "Everything is already up to date" betekent het dat je alles al hebt. Indien dit niet het geval is zal je zien dat hij wat bestanden download of de derde optie is dat er een probleem is ofwel een merge conflict. Hier later meer over.

#// git status

Git status doet exact wat je denkt, het geeft de status weer van jouw lokale bestanden. Status geeft in princiepe weer welke bestande en veranderingen in de volgende commit zitten en ook welke juist niet. Met #// git add <file_name> voeg je bestanden die untracked zijn aan de volgende commit toe. Probeer automatisch gegenereerde bestanden zoals "obj" en de "bin" map van een visual studio project niet te tracken. Indien je dit wel doet zal je continu merge conflicten moeten oplossen, and who got time for that...

#// git add 

Zoals al eerder gezegt voegt git add bestanden toe aan de commit die dus wel getracked moeten worden, dit moet altijd gedaan worden voordat je kan commit. Wil je alle bestanden commiten dan kan je #// git add -a gebruiken. Hiermee voeg je in een keer alle bestanden aan een commit.

