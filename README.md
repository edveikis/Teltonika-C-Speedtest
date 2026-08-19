# Teltonika-c-speedtest

Simple CLI application that measures internet speeds.

Features:
* Measures upload speed
* Measures download speed
* Finds the best server from the list using users location

Built using:
* libcurl
* cJSON
* getopt

## Dependencies

* libcurl

```bash
sudo dnf install libcurl-devel
```

## Building

1. Clone repo

```bash
git clone https://github.com/edveikis/Teltonika-C-Speedtest.git
```

2. cd into it

```bash
cd Teltonika-C-Speedtest
```

3. Build it using `make`

```bash
make
```

## Usage

```bash
./bin/speedtest [OPTIONS]
```

### Options

1. Full automatic test

```bash
./bin/speedtest -a
```

2. Find best server

```bash
./bin/speedtest -b
```

3. Download test

```bash
./bin/speedtest -d -s http://example.com
```

4. Upload test

```bash
./bin/speedtest -u -s http://example.com
```

NOTE: Download and upload can be used in one go.

## Task

Šios užduoties tikslas sukurti programą, naudojant C programavimo kalbą, kuri nustatytų interneto duomenų parsisiuntimo ir išsiuntimo greitį.

Atliekant užduotį, reikia panaudoti šias bibliotekas:
1. libcurl
2. getopt 
3. cJSON

Pridedamas papildomas failas pavadinimu speedtest_server_list.json. Šiame faile yra pateiktas serverių sąrašas, kurie leidžia atlikti duomenų siuntimo testus. Kai kurie serveriai esantys sąraše gali būti nebe veiksnūs.

Programa turi gebėti atlikti šiuos veiksmus:
1. Atlikti duomenų parsiuntimo greičio nustatymo testą;
2. Atlikti duomenų išsiuntimo greičio nustatymo testą;
3. Atlikti geriausio serverio pagal vietovę nustatymą;
4. Atlikti vietovės nustatymą (susirasti API, kuris leistų nustatyti vietovę);
5. Atlikti visą testą automatizuotai;
    
Turi būti galimybė atlikti kiekvieną veiksmą pasirinktinai. 

Atliekant ne pilną testą, o pasirenkant individualų veiksmą, reikia įvertinti kokius parametrus reikia perduoti, kad tą veiksmą būtų galima atlikti. Pvz. Atliekant duomenų parsisiuntimo greitį, šiam veiksmui reikia nurodyti kokį serverį naudoti.

Jeigu atliekamas automatizuotas testas, turi būti sudaryta atitinkama veiksmų seka, kad visi veiksmai būtų atliekami logiškai. 

Duomenų išsiuntimo ir parsiuntimo greitis turi būti išspausdinamas megabitais. 

Duomenų išsiuntimo ir parsiuntimo greičio nustatymo testai turi trukti neilgiau 15 sekundžių. Po 15 sekundžių, veiksmas turi būti stabdomas.

Rezultatus išspausdinti veiksmo pabaigoje, jeigu individualus veiksmas yra atliekamas, kitu atveju po visų veiksmų atlikimo. 

Viso testo metu informuoti vartotoją apie programos statusą/eigą. 

Išspausdinti šiuos duomenis:
1. Duomenų parsisiuntimo greitį;
2. Duomenų išsiuntimo greitį;
3. Serverį, su kuriuo buvo atliktas testas;
4. Vartotojo vietovė. Užtenka valstybės pavadinimo.
    
Implementuoti programoje klaidų valdymo logiką.

Programos rezultatą patalpinti github repozitorijoje. 

Parašyti programos paruošimui Makefile. 
