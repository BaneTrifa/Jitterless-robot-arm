#Zapažanja

Ustanovili smo da je jitter koji se javlja korišćenjem Rpi Pwma u opsegu od 1 - 15 stepeni što je otprilike 0.055 - 0.833 promila (2.555 - 3.333 promila translirano na Rpi Output).

Problem smo rešili donekle korišćenjem prvog načina (pulseIn), ali je problem što servo motor ne pravi smooth pokrete, nego se kreće po pokretima od 15 stepeni

##Korišćenje pulseIn Arduino funkcije

Gledajući source fajl ove funkcije, vidimo da koristi micros() kao način rada i ona je takodje blokirajuća funkcija na odredjen interval, ali je uspelo da nam otkloni jitter u opsegu. Problem predstavlja kada želimo da detektujemo pokret manji od 1 stepen (0.055 promila) jer svaku promenu manju od neke gornje granice detektuje kao jitter i ignorise.
Testirali smo kolike otprilike promene detektuje arduino na pinovima i ustanovili smo da su to promene uglavnom oko 2 stepena pomeraja (0.11 promila) i samim tim nam to predstavlja prepreku za detektovanje manjih pokreta.


TODO:

Osmisliti način da se isčitaju manji pomeraji servo motora na pinu kako se ne bi isflitrirala svaka promena manja od neke gornje granice nego da bude kao obruč (donja granica < jitter < gornja granica).
Trenutnu prepreku za ovaj način predstavlja to što fizički ne možemo isčitati manje pomeraje nego što je opseg jittera.
    
	
##Korišćenje Timera

Pokušali smo na ovaj način odraditi rešenje, medjutim iako smo uspeli isčitati sve vrednosti sa pina i uglove servo motora, nismo uspeli da rešimo problem gde se pojavljuje jitter na arduinu prilikom generisanja novog PWM-a. Moguće je da je problem u tajmingu i da se za neki Timer višestruko koristi i samim tim dolazi do preplitanja prilikom generisanja PWM-a. 

TODO:

Pošto je čitanje pinState-a (RisingEdge interrupt), koristi tajmere koji se takodje koriste i za generisanje PWM-a, potrebno je osmiliti bolju arhitekturu iznova koja će efikasno koristiti tajmere da može dovoljno dobro da čita i generiše jitter free pwm	