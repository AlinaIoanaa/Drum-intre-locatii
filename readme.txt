//Badea Alina Ioana, grupa AB 312
In acest program am salvat informatiile despre fiecare locatie(coordonatele si razele satelitilor si coordonatele locatiei) intr-o lista dublu inlantuita.
Am declarat global prima locatie si doua auxiliare ce servesc la citirea si parcurgerea listei, plus o variabila de tip intreg numita INF, in care am salvat o valoare considerata mai mare decat toate distantele calculate de la o locatie la alta, pe care am atribuit-o ulterior drumurilor avariate.

In functia citireLocatii am citit locatiile si toate informatiile despre ele aflate in fisierul coordonate.in.

In functia coordonateLocatii am calculat coordonatele x si y ale functiilor prin aflarea punctelor de intersectie ale satelitilor.

In functia afisareCoordonate am memorat coordonatele locatilor, in ordine crescatoare, intr-un fisier numit coord_finale.out.

In functiile creareMatriceAdiacenta am creat o matrice patratica pe care ale carei elemente le-am initializat cu 0 si apoi completat cu distantele intre locatii, doua cate doua.

In functia citireSiCompletareAvarii am citit din fisierul avarii.in toate drumurile avariate astfel: am salvat intr-un sir de caractere numit avarie locatiile citite din fisier si am parcurs lista in cadrul unei functii while pana cand sirul avarie s-a identificat cu numele locatiei din lista, memorand numarul acesteia in cadrul a doua variabile ajutatoare numite i si j. Am completat ulterior spatiile specifice acestor drumuri din matricea adiacenta cu valoarea INF.

In functia dijsktra am aplicat algoritmul lui Dijsktra pentru a afla drumul cel mai scurt dintre Locatia1 si locatia citita de la tastatura.

Si in functia distantaMinima am afisat intr-un fisier valoarea drumului cel mai scurt dintre prima locatie si o alta locatie citita de la tastatura. 

In functia dealocare am eliberat memoria ocupata de lista.

Variabilele declarate in functia main:
- coordonate, avarii, coordonate_finale si rezultate reprezinta fisierele de intrare si de iesire
- numarLocatii reprezinta numarul de locatii citite din fisier
- distanta reprezinta distanta minima dintre locatia initiala si cea citita de la tastatura
- startTraseu reprezinta Locatia1
- sfarsitTraseu reprezinta locatia citita de la tastatura
- matriceAdiacenta reprezinta matricea in care au fost memorate costurile dintre doua locatii
- locatie reprezinta locatia citita de la tastatura