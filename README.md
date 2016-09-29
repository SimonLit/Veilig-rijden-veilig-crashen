# VeiligRijdenVeiligCrashen

Stap 1: Installeer Git op je machine https://git-scm.com/downloads
Stap 2: Gebruik de command #cd om te gaan de directory waar je de repository files wilt hebben
Stap 3: Voer de volgende command uit om het project te clonen op jouw computer.
        // git clone https://github.com/SimonLit/VeiligRijdenVeiligCrashen.git
        
Nu heb je alle bestanden van het project op je computer staan, klaar om erin te werken. Maar niet zo snel, eerst een paar essentiele commands.

#// git pull

Git pull kijkt in de repository en gaat na of jij alle bestanden en veranderingen op jouw computer hebt staan. Indien niet zullen deze bestanden en veranderingen gedownload worden. Het is verstandig om regelmatig te pullen als je aan het werken bent aan het project. Zodat je altijd in de meest up to date bestanden aan het werken bent. Dit helpt verkomen van merge conflicten en het maken van dubble code. Indien je een pull doet en je krijgt het bericht "Everything is already up to date" betekent het dat je alles al hebt. Indien dit niet het geval is zal je zien dat hij wat bestanden download of de derde optie is dat er een probleem is ofwel een merge conflict. Hier later meer over.

#// git status

Git status doet exact wat je denkt, het geeft de status weer van jouw lokale bestanden. Status geeft in princiepe weer welke bestande en veranderingen in de volgende commit zitten en ook welke juist niet. Met // git add name_of_file voeg je bestanden die untracked zijn aan de volgende commit toe. Probeer automatisch gegenereerde bestanden zoals "obj" en de "bin" map van een visual studio project niet te tracken. Indien je dit wel doet zal je continu merge conflicten moeten oplossen, and who got time for that...

#// git add 

Zoals al eerder gezegt voegt git add bestanden toe aan de commit die dus wel getracked moeten worden, dit moet altijd gedaan worden voordat je kan commit. Wil je alle bestanden commiten dan kan je // git add -a gebruiken. Hiermee voeg je in een keer alle bestanden aan een commit.

#// git commit -m "commit messages"

We zijn er bijna, nog maar een paar. Met de bovenstaande command leg je jouw veranderingen aan het project vast. Voeg a.u.b een goede commit message toe die duidelijk beschrijft wat je geimplementeerd hebt en of het af is of niet. De veranderingen worden vastgelegd maar ze staan alleen nog op jouw computer nu moet je ze ook uploaden naar de server.

#// git push -u origin branche

Bovenstaand command upload jouw veranderingen naar de server (origin) in de branche die jij zegt. Dit is zeer belangrijk en kom ik later op terug wat nou precies branches zijn en hoe je ze moet gebruiken. Branche moet dus vervangen worden door de branch waarin jij aan het werken bent.

#Branches

Een project moet je eigenlijk als een grote boom zien, en wat heeft een boom ? Takken, ofwel branches. Het nut ervan is dat je delen van je project gescheiden houdt, indien je code aan het maken bent bijvoorbeeld voor de arduino, dan is het belangrijk dat jij de meest up to date bestanden hebt die te maken met de arduino waar jij aan het werken bent. De rest van bestanden heb je even niet nodig en zo is het ook voor andere leden van het project. Dus hoe gaat het nu in zijn werk?

Het is belangrijk dat je in de juiste branch aan het werken bent. Met de command // git branch -l krijg je een lijst van alle branches die erzijn in het project. De branch waar jij in aan het werken bent is groen gemarkeerd met een * ervoor. Standaard sta je in de master branch, dit is echter niet de branch waar je in wilt/moet werken. Om te wisselen van branch type je.

// git checkout name_of_branch

Dus je bent gewisseld van branch, wat nu? Nou nu zit je in de juiste branch, waar jij kan werken en je bestanden kan uploaden. Hoe zit onze structuur in elkaar? We hebben een master branch waar NIET in gewerkt mag worden. Deze dient alleen voltooide onderdelen van het project te hebben. Dan zijn er verscheidende branches die waar wel in gewerkt mag worden op dit moment is de main branch FirstDemo de overige takken zijn niet vertakt vanaf master maar vanaf FirstDemo. Indien jij denkt dat jouw demo voor de volgende presentatie af is kan je in github (de website) een pull request aan vragen. Dit verschuift de code die je in jouw speciefieke branch gemaakt hebt door naar FirstDemo, als een pull request geaccepteerd is wordt de branch verwijdert.
Hieronder staat een schematische voorstellen hoe de branches nou in elkaar zitten.

________MASTER
        |____FirstDemo
                |_______ rp6&arduino
                |_______ netwerk&software
                |_______ smartphone

De bedoeling is dat tijdens het project steeds nieuwe branches gecreerd worden die dan weer via een pull request gemergd worden. Een branch kan in princiepe "communicatie arduino" zijn, dus heb je dat af? Dan kan het doorgeschoven worden naar een tak hoger.
Maar daar hoef je, je nu nog geen zorgen over te maken, met alles wat hierboven staat zou je instaat moeten zijn op het project te clonen, in de juiste branch werken en jouw veranderingen naar de server kunnen pushen.

Indien je meer uitleg wilt of een duidelijk voorbeeld dan raad ik aan het volgend filmpje te kijken (en ook deel 2).
https://www.youtube.com/watch?v=0fKg7e37bQE

