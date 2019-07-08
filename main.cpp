#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include "bazinho.h"

#define MICRO_PER_SECOND 1000000

#define MAP_MIN_X -200
#define MAP_MAX_X 200
#define MAP_MIN_Y -200
#define MAP_MAX_Y 200

// Auxiliary structures
class Vec2
{
    private: // Coordinates
        float x;
        float y;
        
    public:
        Vec2() x(0.0), y(0.0) {}
        Vec2(float vx, float vy): x(vx), y(vy) {}
        
        double len() {
            return sqrt((x * x) + (y * y));
        }
        
        double distTo(Vec2 otherOne){
            Vec2 dif = sub(otherOne);
            return dif.len();
            //return sqrt((otherOne.x - x) * (otherOne.x - x) + (otherOne->y - y) * (otherOne->y - y));
        }
        
        Vec2 add(Vec2 otherOne) {
            Vec2 out;
            out.x = x + otherOne.x;
            out.y = y + otherOne.y;
            return out;
        }
        
        Vec2 sub(Vec2 otherOne) {
            Vec2 out;
            out.x = x - otherOne.x;
            out.y = y - otherOne.y;
            return out;
        }
};

// Organism structures

typedef struct {
    double MIN;
    double MAX;
    double JIT;
} organism_dna_guidelines_tuple;

// - Plant organism
typedef struct {
    //organism_dna_guidelines_tuple GROWTH_SPEED;
    //double PLANT_GROWTH_SPEED_MIN;// 0.1
    //double PLANT_GROWTH_SPEED_MAX;// 1.0
    //double PLANT_GROWTH_SPEED_JIT;// 0.3
    
    organism_dna_guidelines_tuple MATURE_AGE;
    //double PLANT_MATURE_AGE_MIN;// 10.0
    //double PLANT_MATURE_AGE_MAX;// 99.0
    //double PLANT_MATURE_AGE_JIT;// 5.0

    organism_dna_guidelines_tuple PRODUCE_GAP;
    //double PLANT_PRODUCE_GAP_MIN;// 1.0
    //double PLANT_PRODUCE_GAP_MAX;// 10.0
    //double PLANT_PRODUCE_GAP_JIT;// 1.0

    organism_dna_guidelines_tuple LIFESPAN;
    //double PLANT_LIFESPAN_MIN;// 10.0
    //double PLANT_LIFESPAN_MAX;// 30.0
    //double PLANT_LIFESPAN_JIT;// 2.0

    organism_dna_guidelines_tuple CAMOUFLAGE;
    //double PLANT_CAMOUFLAGE_MIN;// 0.0
    //double PLANT_CAMOUFLAGE_MAX;// 10.0
    //double PLANT_CAMOUFLAGE_JIT;// 1.0
} organism_plant_dna_guidelines_t;

// global; Will be populated by main via bin file
organism_plant_dna_guidelines_t organism_plant_dna_guidelines;

class Organism_Plant_DNA {
    private:
        ///float growth_speed;
        float mature_age;
        float produce_gap;
        float lifespan;
        float camouflage;
        
    public:
        Organism_Plant_DNA(): // Generating random values
            //growth_speed(mapRand(organism_plant_dna_guidelines.GROWTH_SPEED.MIN, organism_plant_dna_guidelines.GROWTH_SPEED.MAX)), 
            mature_age(mapRand(organism_plant_dna_guidelines.MATURE_AGE.MIN, organism_plant_dna_guidelines.MATURE_AGE.MAX)),
            produce_gap(mapRand(organism_plant_dna_guidelines.PRODUCE_GAP.MIN, organism_plant_dna_guidelines.PRODUCE_GAP.MAX)),
            lifespan(mapRand(organism_plant_dna_guidelines.LIFESPAN.MIN, organism_plant_dna_guidelines.LIFESPAN.MAX)),
            camouflage(mapRand(organism_plant_dna_guidelines.CAMOUFLAGE.MIN, organism_plant_dna_guidelines.CAMOUFLAGE.MAX))
            { }
            
        Organism_Plant_DNA(Organism_Plant_DNA DNA1, Organism_Plant_DNA DNA2): // Mixing parents DNA + jitter
            //growth_speed((DNA1.growth_speed + DNA2.growth_speed) / 2.0 + mapRand(mapRand(-1 * organism_plant_dna_guidelines.GROWTH_SPEED.JIT, organism_plant_dna_guidelines.GROWTH_SPEED.JIT))), 
            mature_age((DNA1.mature_age + DNA2.mature_age) / 2.0 + mapRand(mapRand(-1 * organism_plant_dna_guidelines.MATURE_AGE.JIT, organism_plant_dna_guidelines.MATURE_AGE.JIT))), 
            produce_gap((DNA1.produce_gap + DNA2.produce_gap) / 2.0 + mapRand(mapRand(-1 * organism_plant_dna_guidelines.PRODUCE_GAP.JIT, organism_plant_dna_guidelines.PRODUCE_GAP.JIT))), 
            lifespan((DNA1.lifespan + DNA2.lifespan) / 2.0 + mapRand(mapRand(-1 * organism_plant_dna_guidelines.LIFESPAN.JIT, organism_plant_dna_guidelines.LIFESPAN.JIT))), 
            camouflage((DNA1.camouflage + DNA2.camouflage) / 2.0 + mapRand(mapRand(-1 * organism_plant_dna_guidelines.CAMOUFLAGE.JIT, organism_plant_dna_guidelines.CAMOUFLAGE.JIT)))
            { }
            
        printSelf() { // My fingers are fuckin cold
            //printf("Growth speed: %.3f\n", growth_speed);
            printf("Maturing age: %.3f\n", mature_age);
            printf("Produce gap: %.3f\n", produce_gap);
            printf("Lifespan: %.3f\n", lifespan);
            printf("Camouflage: %.3f\n", camouflage);
        }
};

class Organism_Plant 
{
    private:
        int id;
        Organism_Plant_DNA DNA;
        int birth_epoch;
        int offspring;
        Vec2 position;
        
    public:
        Organism_Plant(): 
            DNA(),
            birth_epoch(getEpoch()),
            offspring(0),
            position(mapRand(MAP_MIN_X, MAP_MAX_X), mapRand(MAP_MIN_Y, MAP_MAX_Y))
            {}
            
        Organism_Plant(Organism_Plant parent1, Organism_Plant parent2): 
            DNA(parent1.DNA, parent2.DNA),
            birth_epoch(getEpoch()),
            offspring(0),
            position(mapRand(MAP_MIN_X, MAP_MAX_X), mapRand(MAP_MIN_Y, MAP_MAX_Y))
            {}
}

void main(int argc, char *argv[]) {
    //Populate guidelines
    
    //Create IPCs
    
    //Create organisms
    
    //Fire threads (organisms + logger)
    
}

// Auxiliary functions bodies
int getEpoch() {
    struct timeval x;
    gettimeofday(&x);
    return x.tv_sec * MICRO_PER_SECOND + x.tv_usec;
}

double randFloat() {
    return rand() / RAND_MAX;
}

double map(double minX, double maxX, double inVal, double minY, double maxY) {
    return minY + (maxY - minY) * (inVal - minX) / (maxX - minX);
}

double mapRand(double minY, double maxY) {
    return map(0, 1, randFloat(), minY, maxY);
}
