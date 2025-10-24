# Tämä on OAMK Ohjelmistokehitysprojektin harjoitustyö (syksy 2025), tehty ryhmätyönä.
Kyseessä on pankkiautomaatti,
C++/Qt-pohjainen desktop-sovellus, joka käyttää Node.js/Express-REST-APIa ja MySQL-tietokantaa. Qt:n puolella QNetworkAccessManager hoitaa API-kutsut (JSON).

This application is an ATM, Desktop app in C++/Qt consuming a Node.js/Express REST API with a MySQL database. Qt uses QNetworkAccessManager for JSON requests.

# group_5 (alkuperäinen päiväkirjamainen readme)

## Backend alustus (routers & models)
Backend alustettu, routerit ja modelsit luotu / tehty, sekä varmistettu, että toimii

## CRUD operaatiot tehty
Jokaiselle routerille tehty omat POST, PUT, GET ja DELETE operaatiot. Jokainen tehnyt itse omaan routeriin CRUD operaatiot.

## QT applikaatio luotu
QT sovellus aloitettu, taustakuva sovellukselle, reaaliaikainen kello sovellukseen.

## Sovellukseen kirjautumisikkuna luotu
QT sovelluksen aloitus ikkuna luotu, jossa käyttäjä syöttää käyttäjätunnuksen ja pinkoodin.

## Kortin valinta, sekä credit ja debit korteille omat näkymät
QT sovellukseen lisätty credit ja debit ikkunat, sekä QInputDialog dual korttia varten, jossa käyttäjä valitsee debitin tai creditin

## Virtuaali näppäimistön luonti
QT sovellukseen lisätty virtuaali näppäimistö, jota käyttäjä voi hyödyntää kirjautumisessa sekä nostossa.

## Aikakatkaisu credit ja debit ikkunoihin
QT sovellukseen lisätty aikakatkaisu, joka palaa kirjautumis sivulle, jos käyttäjä on inaktiivinen 30 sekunttia.

## Credit ikkunaan luotu valikko tapahtumille
QT sovellukseen lisätty valikko StackedWidgetin avulla, josta käyttäjä voi valita noston, creditlimitin ja tilitapahtumat. 

## Nosto ikkuna luotu
QT sovellukseen luotu näkymä, josta käyttäjä voi nostaa 20, 40, 50, 100 tai muun summan (10 euron tarkkuudella). Creditlimit päivittyy reaaliajassa, jokaisen noston yhteydessä. 

## Tilitapahtumat näkymä luotu
QT sovellukseen luotu näkymä, johon listautuu käyttäjän tilitapahtumat uusimmasta vanhimpaan.

## Debit ikkunaan lisätty samat toiminnot kuin credit ikkunaan

## Ulkonäköä päivitetty
Credit ja debit ikkunoiden ulkonäköä päivitetty. Buttonit, virtualkeyboard ja line edittejä siistitty.

## TableView päivitetty ja kirjautumisikkunan tiedot tyhjennetty
TableViewtä säädetty näyttämään 10 viimeisintä tilitapahtumaan ilman scrollausta. Kirjautumisikkunasta poistettu tiedot näkyvistä, kun debit tai credit ikkuna aukaistaan.
