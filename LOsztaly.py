import math

import redis

class LOsztaly():
    def __init__(self):
        redis_host='172.22.221.190'
        redis_port=6379

        self.r=redis.Redis(host=redis_host,port=redis_port,
                           decode_responses=True)

    def torles(self):
        self.r.delete("lo_azon")
        self.r.delete("s_lovak")

    def kiiratas(self):
        print(self.r.keys("*"))


    #ló tábla inicializálása
    def uj_lo(self,nev,leiras,nem,szul_dat):
        loazon=str(self.r.incr("lo_azon"))
        self.r.hset("h_lo_"+loazon,mapping={
            'nev':nev,
            'leiras':leiras,
            'nem':nem,
            'szul_dat':szul_dat
        })
        self.r.sadd("s_lovak",loazon)
        return loazon


    #Lovak listázása
    def lolista(self):
        print("=== Lovak listázása ===")

        for i in self.r.smembers("s_lovak"):
            lo_adatok = self.r.hgetall("h_lo_" + i)

            print(f"\nLovak azonosítója: {i}")
            print("-" * 30)

            for j, ertek in lo_adatok.items():
                print(f"{j}: {ertek}")

            print("=" * 30)

    #verseny tábla inicializálása
    def uj_verseny(self,datum,helyszin):
        versenyazon=str(self.r.incr("verseny_azon"))
        self.r.hset("h_verseny_",versenyazon,mapping={
            'datum':datum,
            'helyszin':helyszin
        })
        self.r.sadd("s_versenyek",versenyazon)
        return versenyazon

    #verseny listázása
    def versenylista(self):
        for i in self.s.smembers("s_versenyek"):
            for j in self.r.keys("h_verseny_",i):
                print(j)
                print(self.r.hget("h-verseny_",i,j))

    #lo nevezése egy versenyre
    def lo_nevezes(self,loazon,versenyazon):
        if not(self.r.sismember("s_versenyek",versenyazon)):
            print("Nincs ilyen verseny")
            return
        if not(self.r.sismember("s_lovak",loazon)):
            print("Nincs ilyen lo")
            return

        if self.r.zscore("z_verseny_lovai"+versenyazon,loazon)!=None:
            print("Már versenyzett")
            return
        self.r.zadd("z_verseny_lovai_",{0,loazon})

    #futamszervezés funkcionalitasbol
    def futam_szervezes(self,versenyazon):
        if not(self.r.sismember("s_versenyek",versenyazon)):
            print("Nincs ilyen verseny")

        #hány db lo van
        db=self.r.zcard()

        #hany db futam van
        futam_db=math.ceil(db/6)

        for i in range(futam_db):
            futamazon=str(self.r.incr("futam_azon"))

            self.r.sadd("s_verseny_futamai"+versenyazon,futamazon)

            for j in self.r.zrange("z_verseny_lovai_"+versenyazon,0+i*6,5+i*6):
                self.r.zadd("z_futam_lovai_"+versenyazon+"_"+futamazon,{0,j})

    #futamok listázása
    def futam_lista(self,versenyazon):
        for i in self.r.smembers("s_verseny_futamai"+versenyazon):
            print("futamazon:"+i)
            for j in self.r.zrange("z_futam_lovai_"+versenyazon+"_"+i):
                print(j)

    #ido hozzaadasa egyes lovakhoz,akik futamokon vannak
    def ido_hozzarendeles(self,versenyazon,futamazon,loazon,ido):
        if self.r.zscore("z_futam_lovai_" + versenyazon + "_" + futamazon,loazon)!=0:
            print("Nincs hozzárendelve,vagy már kapott időt a ló")
            return
        self.r.zadd("z_futam_lovai_" + versenyazon + "_" + futamazon, {ido, loazon})
        self.r.zadd("z_verseny_lovai_", {ido, loazon})


    def futam_eredmeny(self,versenyazon):
        for i in self.r.zrevrange("z_verseny_lovai_" + versenyazon,0,-1):
            print(i)
            print(i[0])
            for j in self.r.hgetall("h_lo_"+i[0]):
                print(j)

