Echipa : CheckMates
Capitan : Dumitrescu Georgiana
Membrii echipei : Belbu Alexandru, Dumitrescu Georgiana, Manescu Emilian
Grupa : 324, 323
Seria : CB
Titular de curs : Rebedea Traian

Am decis implementarea solutiei in limbajul C++ pentru a facilita rularea
programului intr-un timp scurt .

INSTRUCTIUNI DE COMPILARE
 	
 	Arhiva contine un fisier de Makefile care va permite rularea corecta a
 	programului prin rularea urmatoarelor comenzi in ordinea precizata :
 		$ make
		$ xboard -fcp "make run" -scp "fairymax" -secondInitString "new\nrandom\nsd 2\n" -tc 5 -inc 2 -autoCallFlag true -mg 10 -sgf partide.txt -reuseFirst false 

 		-> Se asteapta pornirea jocului
 		-> make clean (*optional la finalul executiei)
 		
STRUCTURA PROIECTULUI

	Dupa cum se observa, arhiva contine 5 fisiere care sustin implementarea
	solutiei finale .

	1. main.cpp
	2. Moves.cpp
	3. Board.cpp
	4. Evaluation.cpp
	5. Minimax.cpp
	6. Legal_Moves.h
	7. Board.h
	8. Evaluation.h
	9. Minimax.h

	Fisierele Legal_Moves.h, Board.h, Minimax.h si Evaluation.h contin 
	antetele functiilor implementate in Moves.cpp, Board.cpp, Minimax.cpp si Evaluation.cpp
	si utilizate mai departe in oricare dintre cele 5 fisiere .cpp.

DESCRIEREA SOLUTIEI

	Pentru o implementare eficienta a solutiei pentru proiect, s-a decis 
	utilizarea BitBoard-urilor in reprezentarea tablei de sah. Pentru
	o folosire corecta a tuturor pieselor, neputand fi folosita o singura
	tabla (un singur bitboard), au fost create 15 BitBoard-uri care au 
	urmatoarele functionalitati:

		board -> Placa completa de sah (toate piesele)

		PLACI PARTICULARE:

			white_pawns -> Placa pionilor albi
			white_rooks -> Placa turelor albe
			white_knights -> Placa pentru caii albi
			white_bishops -> Placa nebunilor albi
			white_queen -> Placa reginei/reginelor albe
			white_king -> Placa regelui alb
	
			black_pawns -> Placa pionilor negri
    		black_rooks -> Placa turelor negre
			black_knights -> Placa pentru caii negri
			black_bishops -> Placa nebunilor negri
			black_queen -> Placa reginei/reginelor negre
			black_king -> Placa regelui negru

			black_board -> Placa pieselor negre
			white_board -> Placa pieselor albe

	Pentru a facilita lucrul cu aceste placi, au fost incluse in structura
	ChessBoard. Aceasta cuprinde toate tipurile de BitBoard-uri mentionate
	mai sus, precum si un bool pentru a determina daca starea curenta a 
	tablei corespunde finalului jocului.

	!! Fisierul Board.h include structura de date BitBoard care descrie
	campurile placilor de tip BitBoard (create si folosite dupa cerintele
	programului). 

		-> Campul "engine_color" va fi folosit pentru salvarea culorii
		pe care joaca engine-ul. Acesta este setat pentru board si 
		folosit mai departe in verificari
		-> Campul "color" este setat pentru
		placile particulare si determina ce culoare sunt piesele care apartin
		respectivei placi 
		-> Campul "force_mode" este setat pentru board si este true daca
		tabla se afla in force mode si false, altfel
		-> Campul "current_form" este numarul de tipul unsigned long long int
		care reprezinta forma curenta a tablei, bitii de 1 fiind pozitiile 
		ocupate de piese, iar bitii de 0 fiind pozitiile libere. Acest camp
		este cel mai utilizat, determinand posibile miscari de deplasare sau
		atac, dar si finalitatea jocului de sah prin verificarea existentei
		unei miscari urmatoare.
		-> Campurile "first_move_king", "first_move_rook1", "first_move_rook2"
		verifica daca mutarea care urmeaza a fi facuta cu regele sau tura
		respectiva ar fi prima. Sunt folosite pentru a putea include rocada
		in mutarile posibile ale regelui. Sunt caracteristice fiecareia dintre
		tablele "white_board" si "black_board".
		-> Campul "en_passant" este folosit pentru a verfica daca un pion poate
		face mutarea respectiva. Dupa ce un pion se muta cu doua pozitii in fata,
		aceasta variabila este initializata cu un numar pe 64 de biti, in care
		un singur bit este setat (cel cu o pozitie imediat mai jos de pozitia
		pe care se plaseaza pionul, adica locul in care un pion care face 
		en passant ar ajunge). Dupa apelul functiilor de mutare (adica apply_move
		pentru engine, sau xboard_move, pentru adversar), variabilele tablei
		opuse se seteaza cu 0 (pentru a denota ca en passant se poate face
		doar imediat dupa mutarea cu doua pozitii a pionului).

	Tot in fisierul Board.h sunt incluse antetele functiilor implementate in
	Board.cpp:

		~ piece_type -> Primeste pozitia din tabla care se verifica, sub forma
		unui numar unsigned long long int, si tablele componente ale pieselor.
		In functie de tabla care are o pozitie ocupata ce coincide cu pozitia 
		studiata, se va returna un string care contine ce fel de piesa se
		afla pe pozitia verificata .
			Exemplu : Daca se verifica AND intre pozitia studiata si tabla
			pionilor albi, inseamna ca s-a gasit aceeasi pozitie ocupata in
			cele doua, deci piesa verificata face parte din tabla pionilor
			albi si se va returna stringul "white pawn".

		~ reset_pieces_position -> Reseteaza o tabla particulara dintre cele
		mentionate mai sus, in functie de culoarea si tipul transmise ca 
	 	parametrii

	 	~ reset_all_pieces -> Reseteaza toate tablele particulare mentionate
		mai sus, folosindu-se de functia reset_pieces_position

		~ set_engine_color -> Seteaza culoarea engine-ului pentru tabla 
		transmisa ca parametru, pe culoarea transmisa si ea ca parametru

		~ new_board -> Seteaza toate pozitiile initiale ale pieselor, 
		indiferent de culoarea sau tipul acestora. Functia este folosita
		in setarea placii board

		~ resign -> Transmite mesajul de resign xboard-ului, folosindu-se de
		culoarea engine-ului transmis prin parametrul board

		~ force_mode_on / force_mode_off -> Seteaza campul force_mode al
		placii transmise ca parametru

		~ update_board -> face operatia de SAU intre toate tablele de
		fiecare culoare, pentru a actualiza tablele dupa o mutare

	!! Fisierul Legal_Moves.h include structura de date Piece care descrie
	campurile unei instante(piesa de pe tabla).
 
		-> Campul "possible_moves" stabileste lista de mutari posibile ale
		piesei curente, din pozitia in care se afla

		-> Campul "number_of_moves" reprezinta numarul de mutari posibile
		ale piesei curente, din pozitia in care se afla (in eventualitatea
		gasirii acestui camp ca avand valoarea 0, se considera ca piesa nu
		mai poate fi mutata din pozitia in care se afla)

	Tot in fisierul Legal_Moves.h se afla antetele functiilor implementate
	in Moves.cpp: 

	~ bits_to_position_string -> Functia va primi o pozitie din tabla de sah
	(BitBoard) prin parametrul current_position si va determina string-ul care
 	carcaterizeaza aceasta pozitie
 		Exemplu : 00...000100 reprezinta pozitia "c1"(coloana "c" de pe randul
 		1 din placa)

 	~ pos_to_64bits -> Primeste un string cu pozitia unei piese si returneaza
 	pozitia acesteia pe tabla, printr-un numar unsigned long long int 
 	(inverseaza efectul functiei bits_to_position_string)

 	~ regular_move_message -> Transmite xboard-ului miscarea engine-ului, daca
 	acesta nu reprezinta un caz particular de miscare

 	~ pawn_promotion_message -> Trasmite xboard-ului miscarea engine-ului, 
 	daca aceasta reprezinta o miscare de tipul pawn promotion

 	~ index_bit -> Primeste ca parametru, pozitia unei piese pe tabla si
 	stabileste indexul acesteia in tabla .
 		Exemplu : index_bit(00...0010) = 2

 	~ check_first_move -> Primeste culoarea si pozitia unui pion si determina
 	daca mutarea pe care urmeaza sa o faca este prima pentru aceasta piesa
 	sau nu

 	~ place_piece -> Modifica pozitia unei piese pe tabla data ca parametru
 	prin mutarea acesteia de la sursa la destinatie, fara alte operatii

 	~ make_move -> Se foloseste de functia place_piece si, in functie de
 	tipul de tabla pe care se gaseste sursa (pioni albi, regina neagra,etc),
 	va modifica tablele aferente din care piesa face parte. La final se
 	actualizeaza forma tablei board

 	~ castling -> Verifica forma comenzii primite ca parametru si, in functie
 	de sursa si destinatia pe care le include aceasta, se va folosi de functia
 	make_move pentru a executa miscarea transmisa de xboard

 	~ pawn_promotion -> Se foloseste de sursa, destinatia si placile trasnmise
 	ca parametrii pentru a executa miscarea de pawn_promotion daca este cazul.
 	La final, se actualizeaza placa reginei de aceeasi culoare cu a pionului
 	care a fost promovat

 	~ delete_piece -> Se foloseste de parametrii destination si color 
 	transmisi functiei pentru a sustrage piesa de pe pozitia destination din 
 	placile aferente

 	~ attack_move -> Extrage piesa de pe pozitia destination, folosind functia
 	delete_piece pentru a actualiza placa "atacata"

 	~ attack_move_pawn -> se foloseste de functia precedenta pentru a sterge
 	piesa atacata, dar mai are doua verificari pentru mutarea de en passant
 	(pe care doar un pion o poate face)

 	!!! Functiile de miscari particulare !!!

 	Functiile : pawn_moves, rooks_moves, knight_moves, bishop_moves,
 	queen_moves si king_moves se bazeaza pe aceleasi principii, dar folosite
 	pentru a retine diferitele miscari pe care acestea pot sa le execute.
 	Pe baza formelor placilor transmise ca parametrii (black_board si 
 	white_board), se verifica in toate directiile considerate ca si posibile
 	miscari pentru piesa curenta si, in cazul gasirii unei mutari posibile
 	pentru aceasta piesa, se va retine in vectorul possible_moves al piesei
 	curente, aceasta optiune.

 	Toate aceste functii, cu exceptia functiei queen_moves verifica prin
 	operatii de AND cu forma tablei, daca se pot misca in diferite directii,
 	si vor retine in vector, string-ul returnat de bits_to_position_string,
 	aplicat pentru pozitia gasita ca o posibila miscare pentru piesa.

 	queen_moves imbina functiile rooks_moves si bishop_moves pentru a crea
 	vectorul de miscari posibile ale reginei

 	~ no_moves_left -> Calculeaza o suma de miscari totale, adunand numarul
 	de miscari posibile ale fiecarui pion de pe tabla selectata . Daca aceasta
 	suma este 0 la final, adica numarul de miscari aferent fiecarui pion este
 	0, atunci functia va returna true (nu mai exista un pion care se poate
 	misca)

 	~ is_check -> Va porni de la pozitia curenta a regelui. Se seteaza placile
 	oponentului, in functie de culoarea cu care joaca bot-ul echipei 
 	(transmisa ca parametru). In continuare, se vor parcurge toate directiile
 	posibile, pornind de la pozitia curenta a regelui, pana se intalneste o
 	alta piesa. Daca piesa intalnita face parte din piesele oponentului si 
 	poate ataca regele, atunci regele se considera in sah. Se verifica in toate
 	directiile, daca regele oponent se afla la o pozitie distanta de pozitia 
 	regelui verificat. Pe fiecare diagonala, se verifica daca regele verificat
 	se afla in raza de atac a unui pion al oponentului. Se va verifica la final
 	daca pozitiile curente ale cailor reprezinta o amenintare pentru rege. 

 	~ multiple_positions_check -> Aceasta functie verifica, pe baza pozitiei
 	regelui si a unei pozitii destinatie, daca fiecare pozitie prin care
 	regele trece deplasandu-se spre destinatie, este o pozitie sigura (regele
 	nu se afla in sah in aceasta pozitie). Functia este utilizata in vederea
 	includerii mutarii de castling intre mutarile posibile ale regelui verificat.
 	Daca regele trece de celelalte conditii impuse si, in plus, toate pozitiile
 	aflate intre el si tura implicata in castling nu sunt pozitii de sah pentru
 	rege (adica functia returneaza true), se valideaza faptul ca mutarea de
 	castling este o mutare posibila pentru rege.

 	~ xboard_move -> Obtine sursa si destinatia din input-ul transmis si, pe
 	baza acestora, decide placa de pe care se muta si se foloseste de 
 	functiile attack_move, attack_move_pawn (pentru pioni) si make_move pentru 
 	a actualiza forma placilor. Este utilizata variabila is_pawn care este true
 	daca sursa mutarii (piesa care se muta) este un pion. Aceasta este utilizata
 	pentru a decide ce functie de atac se foloseste, si mai departe in determinarea
 	miscarii de pawn_promotion (daca se respecta conditiile acestui caz). Se
 	verifica daca dupa mutarea data, se poate actualiza variabilele en_passant (se
 	seteaza pentru tabla care a facut mutarea, daca este cazul, si se seteaza la 0,
 	pentru tabla adversa). La final, se verifica daca numarul de piese ramase pe
 	tabla este mai mic sau egal decat 12, caz in care se seteaza bool-ul endgame
 	la true.

 	~ no_pieces_rook_king -> Verifica daca intre rege si cele doua ture nu 
 	exista alte piese (conditie pentru rocada). Se foloseste de doua variabile:
 		- first, care ia valoarea 1 daca intre rege si tura din stanga tablei
 		nu exista nicio piesa
 		- second, care ia valoarea 2 daca intre rege si tura din dreapta tablei
 		nu exista nicio piesa
 	si returneaza suma dintre ele ca rezultat. Astfel, se returneaza:
 		- 1, daca doar intre rege si prima tura se poate face rocada
 		- 2, daca doar intre rege si a doua tura se poate face rocada
 		- 3, daca se poate face intre rege si ambele ture

 	!! Fisierul main.cpp reprezinta fisierul principal al proiectului in care 
 	se prelucreaza comenzile primite si se executa diferite mutari pe baza
 	acestora.

 	~ check_regular_input/check_pawn_p_input -> Verifica daca inputul primit
 	este corect si returneaza o variabila booleana in functie de rezultat

 	~ MAIN -> Se declara tabla folosita pentru jocul de sah (ChessBoard)
 		-> Se apeleaza functiile reset_all_pieces si new_board pentru a 
 		construi reprezentarile placilor
 		-> Se apeleaza functiile set_engine_color si force_mode_off pentru a
 		seta culoarea engine-ului si parametrul force_mode pe false pentru
 		placa
 		-> Se foloseste o variabila color_on_move pentru a comuta intre cele
 		doua placi care executa miscari. Aceasta isi va schimba valoarea
 		dupa fiecare mutare
 		-> Se foloseste while(1) pentru a citi input-uri de la xboard pana se
 		da o comanda de return care sa intrerupa continuarea jocului.
 		-> La fiecare input citit se actualizeaza placile 
 		-> Mai departe se citeste input-ul si in functie de forma acestuia, se
 		vor apela functiile implementate si descrise anterior . 
 		-> Comenzile black/white vor modifica parametrul engine_color din 
 		structura placii

 		-> In cazul primirii unui input de mutare valid, daca parametrul
 		force_mode este false(adica nu ne aflam in force_mode), se va
 		interpreta acest input si conform datelor oferite de acesta, se va
 		modifica placa prin apelarea comenzii xboard_move, iar apoi se va 
 		apela functia alfabetaRoot pentru a executa mutarea engine-ului, cu
 		ajutorul algoritmului Negamax. Se trateaza separat rocada. Algoritmul
 		de Minimax se apeleaza cu un depth de 5.

 		-> In cazul comenzii "force", se va seta parametrul force_mode al 
 		placii pe true, iar mai departe, la urmatorul input primit, se va 
 		verifica board.force_mode = true si daca input-ul primit este valid,
 		se va proceda ca in cazul mutarii primite de la xboard(functia 
 		xboard_move).

 		-> Comanda "go" va seta parametrul board.force_mode pe false si jocul
 		se va continua in functie de culoarea care este pe move.

	!! Fisierul Evaluation.h contine constante si functii folosite pentru a
	calcula scorul unei table la un anumit moment de timp.
	S-au asignat fiecarui tip de piesa urmatoarele scoruri:
		- Pion: 100
		- Cal: 320
		- Nebun: 330 
		- Tura: 500
		- Regina: 900
		- Rege: 20000

	Fiecare tip de piesa are o matrice care contine scorul asociat fiecarei
	pozitii din tabla, cu importanta deosebita pentru pozitiile centrale ale
	tablei (in care exista mai multa mobilitate). Regele are doua tipuri de
	matrici, una pentru inceputul jocului si una pentru finalul jocului.

	De asemenea, in Evaluation.h se afla antetele functiilor care calculeaza
	propriu zis scorul unei table:
		- pawn_eval: calculeaza scorul asociat pionului respectiv
		- table_value: calculeaza scorul tablei doar pe baza pieselor, fara a
		lua in calcul pozitiile lor
		- evaluate: se foloseste de functiile de mai sus pentru a calcula
		scorul tablei unui jucator
		- evaluateBoardScore: calculeaza diferenta dintre scorurile celor
		doi jucatori.

	!! Fisierul Evaluation.cpp
	
	Functii:
		~ table_value: cauta in toata tabla fiecare piesa a jucatorului
		reprezentat de variabila player (este 1 pentru alb, si -1 pentru
		negru) si adauga la scor ponderea piesei respective.

		~ pawn_eval: pentru un pion a carui pozitie este data ca parametru,
		se calculeaza urmatoarele:
			- se penalizeaza pionii de pe marginea tablei
			- se penalizeaza pionii aflati unul langa celelalt, deoarece
			nu se pot apara reciproc

		~ evaluate: calculeaza scorul unei table folosindu-se de functiile
		precedente si de matricile din Evaluation.h. De asemenea, se adauga
		puncte bonus pentru ambii nebuni pe tabla, in endgame, nebunul este
		mai valoros decat calul (deoarece poate da sah mai usor) si este
		incurajata rocada (cu ajutorul bool-ului castled).

		~ evaluateBoardScore: face diferenta intre scorurile celor doi
		jucatori.

	!! Fisierul Minimax.h contine antetele unor functii folosite pentru
	algoritmul Minimax:
		~ get_attack_moves: adauga intr-un vector doar capturile

		~ get_possible_moves: adauga intr-o pereche de vectori
		atat capturile, cat si mutarile "quiet", care nu iau alte
		piese.

		~ apply_move: functioneaza asemanator cu functia xboard_move
		din Moves.cpp

		~ alfabeta_root: functie ajutatoare care permite algoritmului
		de minimax sa intoarca doar scorul unei pozitii (si nu o pereche
		de tip scor-mutare).
 
		~ alfabeta_negamax: algoritmul negamax cu alfa beta pruning

		~ Quiescence: nefolosit inca, dar implementat. Va fi folosit
		pentru a rezolva problema "horizon effect", in care o mutare
		pare favorabila la o cautare cu un depth fix, dar care poate
		de fapt sa duca intr-o stare care duce la esec.

	!! Fisierul Minimax.cpp contine implementarile functilor din
	Minimax.cpp.
	
	!! Fisierul Minimax.cpp

	Functii:
		~ get_attack_moves: iterand prin fiecare pozitie de pe tabla de sah
		  genereaza toate mutarile de attack ale jucatorului care are
		  culoarea <color>

		~ get_possible_moves: itereaza prin fiecare pozitie de pe tabla de
		  sah si genereaza toate mutarile posibile in functie de starea
		  data ca parametru <chess> impartindu-le in acelasi timp in doua
		  submultimi(mutari de attack-> <killers> ; mutari quiet-> <quiet>)

		~ apply_move

		~ sortMoves: generand toate state-urile posibile ale jocului se
		  returneaza multimea ordonata a acestora in functie de scorul
		  boardului curent

		~ alfabeta_root: implementarea algoritmului de tip minimax folosind
		  optimizarea alfabeta pruning; functia va evalua mai intai
		  "profitul" fiecarei miscari move provenita din multimea all_moves
		  evaluand mai intai miscarile de attack pentru a putea avea cat
		  mai multe taieri ale arborelui

		~ alfabeta_negamax: intoarce evaluarea cea mai "profitabila" a
		  subarborelui provenit din alfabeta_root

		~ Quiescence: functioneaza asemanator cu negamax, dar verifica recursiv
		  doar mutarile de atac, pana se ajunge intr-o stare "quiet", in care 
		  nu se mai poate face nicio captura. Nu este adaugata inca in
		  algoritmul de minimax, din cauza timpului de executie.

DETALII DESPRE IDEI & DOCUMENTATIE

	Etapa 1

	Am acordat cateva zile inainte de inceperea proiectului pentru a gasi
	impreuna cu echipa mea, o solutie eficienta pentru miscarile pieselor
	de sah si reprezentarea tablei si dupa o serie de idei si cateva
	pagini citite, am gasit ca mod de reprezentare a tablei, BitBoard-urile.
	Stabilind impreuna ca ar fi o idee buna datoria eficientei operatiilor
	pe biti, am continuat cu aceasta idee si mai departe am stabilit ca vom
	avea nevoie de mai mult de o placa pentru a putea realiza jocul, deoarece
	folosind doar una, nu vom putea identifica tipul si culoarea placii .
	Dupa cum am descris mai sus, mutarile posibile, atacurile si orice fel
	de modificare adusa tablelor se realizeaza prin operatii de AND, OR si 
	XOR, fara alte operatii costisitoare. Au fost folosite structuri pentru
	a limita numarul de variabile utilizate si am limitat numarul de 
	verificari pe care le executa programul prin asigurarea validarii unui
	singur if si daca se gaseste un caz favorabil, nu se mai continua cu o 
	alta verificare (in cazul main-ului).

	Etapa a 2-a
	
	Pentru aceasta etapa, baza proiectului a fost pusa utilizand cunostintele
	acumulate in cadrul cursului/laboratorului de Minimax. Pentru imbunatatirea
	algoritmilor utilizati, au fost cautate solutii pentru evitarea unor mutari
	dezavantajoase si reducerea cazurilor inutile luate in considerare (prin
	efect, am reusit sa reducem si timpul necesar deciziei urmatoarei mutari).
	Solutiile gasite si luate in considerare (o parte putand fi observate in
	implementarea aleasa) au fost inspirate din urmatoarele surse:

	1) https://www.freecodecamp.org/news/simple-chess-ai-step-by-step-1d55a9266977/
	2) http://people.oregonstate.edu/~machao/CVpage/MaChao_files/learning_chess.pdf
	3) https://www.chessprogramming.org/Evaluation

RESPONSABILITATI

	Etapa 1

	Am decis impreuna solutiile potrivite si ce modalitati de implementare
	am folosit. A fost discutat in echipa totul, de la modul de reprezentare
	a placii, pana la exceptiile jocului si cazurile particulare ale mutarilor.
	Implementarea functiilor din fisierul Moves.cpp a fost realizata de mine
	(Dumitrescu Georgiana), impreuna cu fisierul Legal_Moves.h, precum si 
	interpretarea comenzilor in main si cele 2 functii suplimentare adaugate
	in fisierul main.cpp. Makefile-ul a fost realizat de Manescu Emilian . 
	La functiile din Board.cpp (si implicit declararea acestora in Board.h), 
	am lucrat toti 3 impreuna, adaugand functii in mod egal, dupa necesitate.
	Cele doua structuri (Piece si BitBoard) au fost realizate de comun acord
	dupa o forma stabilita la inceput . Toti 3 membrii echipei am luat parte
	la testarea proiectului in forma finala si aducerea modificarilor bazate
	pe rezultatele testelor.

	Etapa a 2-a
	
	Dumitrescu Georgiana:
		- modificare solutie is_check
		- implementare multiple_positions_check
		- modificare mod de apelare functii de generare a mutarilor pieselor
		- debugging

	Belbu Alexandru:
		- o parte din get_possible_moves
		- sort_moves
		- alfabeta_root
		- alfabeta_negamax
		- debugging

	Manescu Emilian:
		- implementare en_passant
		- o parte din rocada (la adaugarea mutarile posibile ale regelui)
		- implementarea functiei apply_move
		- implementarea functiei de evaluare
		- adaugarea clasei ChessBoard
		- Quiescence Search
		- documentatie
		- debugging