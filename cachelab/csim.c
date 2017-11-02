#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


//various datatypes to build the cache
typedef unsigned long long unsigned64;
typedef struct{
    int s;//S=2^s
    int b;//B=2^b
    int S;//Number of sets
    int B;//Block size
    int E;//Associativity
    } cacheStatus;

typedef struct {
    int validBit;
    unsigned64 tag;
    int accessRecord;
} LINE;

typedef struct {
   LINE *lines;
} SET;

typedef struct {
    SET *sets;
} CACHE;

//fucntion to set cache
CACHE setCache(unsigned64 S, int E) 
{
    CACHE Cache;	
    SET set;
    LINE line;
    Cache.sets = (SET *) malloc(sizeof(SET) * S);
    //construct cache sets
    int i;
    for (i = 0; i < S; i++) 
    {
        set.lines =  (LINE *) malloc(sizeof(LINE) * E);
        Cache.sets[i] = set;
        //construct cache lines
        int j;
        for (j = 0; j < E; j++) 
        {
            line.validBit = 0; 
            line.tag = 0; 
            set.lines[j] = line;
            line.accessRecord = 0;
        }
    } 
    return Cache;
}

//printUsage function
void printUsage(){
    printf("Usage: ./csim-ref [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n");
    printf("-s <s>: number of set index bits\n");
    printf("-E <E>: Associativity\n");
    printf("-b <b>: number of block bits\n");
    printf("-t <tracefile>: Name of the valgrind trace to replay\n");
}
//method to check hit
int Hit(LINE line,unsigned64 tag){
    if(line.validBit&&line.tag == tag){
        
            return 1;
        
    }
    return 0;
}
//method to check full
int Full(SET set, cacheStatus status){
    int i;
    for(i = 0; i<status.E; i++){
        if(set.lines[i].validBit==0){
            return 1;
        }
    }
    return -1;
}
//method to find the next open line
int findIndex(SET set, cacheStatus status){
    int i;
    for(i = 0; i<status.E; i++){
        if(set.lines[i].validBit== 0){
            return i;
        }
    }
    //not found
    return -1;
}
//method to find the line to evict
int toEvict(SET set, cacheStatus status){
    int min = set.lines[0].accessRecord;
    int index=0;
    int i;
    for(i = 0; i < status.E ; i++){
        if(min>set.lines[i].accessRecord){
            index = i;
            min = set.lines[i].accessRecord;
        }
    }
    return index;
}

int maxIndex(SET set, cacheStatus status){
    int max = set.lines[0].accessRecord;
    int i;
    int index = 0;
    for(i = 0; i < status.E ; i++){
        if(set.lines[i].accessRecord>max){
            index = i;
            max = set.lines[i].accessRecord;
        }
    }
    return index;
}


//global variables to record hit,miss and evict
int hit_count=0;
int miss_count=0;
int eviction_count=0;

//simulator function
cacheStatus simulator(CACHE Cache,cacheStatus status, unsigned64 address){
    //compute the tag size
    int tagSize = 64-(status.b + status.s);
    //assign tag
    unsigned64 tag = address >> (64-tagSize);
    
    //compute for the set index
    unsigned64 setIndex = address << tagSize >> (64-status.s);
    //assign set
    SET set = Cache.sets[setIndex];
    
    //loop lines
    int i;
    int hit = 0;
    for (i = 0; i<status.E; i++){
        LINE currentLine = set.lines[i];
        //check if there is a hit
        if(Hit(currentLine, tag)){
            //if hit=1(true), update info in the status
            hit_count++;
            int max = 0;
            hit = 1;
            max = maxIndex(set, status);
            Cache.sets[setIndex].lines[i].accessRecord = Cache.sets[setIndex].lines[max].accessRecord+1;
        }
    }
    if(hit == 0 && Full(set, status) == 1){
    //if not full then it is a miss, update the info in the status
        miss_count++;
        int index = 0;
        index = findIndex(set, status);
        set.lines[index].tag = tag;
        set.lines[index].validBit= 1;
        int max = 0;
        max = maxIndex(set, status);
        Cache.sets[setIndex].lines[index].accessRecord = Cache.sets[setIndex].lines[max].accessRecord+1;
    }else if(hit == 0){
        //evict, update the info in the status&set
        miss_count++;
        eviction_count++;
        int evictIndex = 0;
        //find the evict line
        evictIndex = toEvict(set, status);
        set.lines[evictIndex].tag = tag;
        int max = 0;
        max = maxIndex(set, status);
        Cache.sets[setIndex].lines[evictIndex].accessRecord = Cache.sets[setIndex].lines[max].accessRecord+1;
    }
    return status;
}
//main function
int main(int argc, char** argv)
{
    CACHE Cache;
    cacheStatus status;
    //store file trace
    char* trace;
    char input;
   
    //read in input
    while( -1!=(input=getopt(argc,argv,"s:E:b:t:")))
    {
        switch(input){
        case 's':
            status.s=atoi(optarg);
            status.S =1<<status.s;
            break;
        case 'E':
            status.E = atoi(optarg);
            break;
        case 'b':
            status.b=atoi(optarg);
	    status.B =1<<status.b;
            break;
        case 't':
            trace = optarg;
            break;
        default:
            printUsage();
            break;  
        }
    }
    //set cache
    Cache= setCache(status.S, status.E);
    //input file
    FILE *file;
    //wrap the trace into file
    char instruction;
    unsigned64 address;
    int size;
    file = fopen(trace, "r");
    while(fscanf(file, " %c %llx,%d", &instruction, &address, &size) == 3){
        switch(instruction){
             case 'L':
                status = simulator(Cache, status, address);
                break;
            case 'S':
                status = simulator(Cache, status, address);
                break;
            //M should run twice
            case 'M':
                status = simulator(Cache, status, address);
                status = simulator(Cache, status, address);	
                break;
            default:
                break;
        }
    }
    fclose(file);
    //final result
    printSummary(hit_count, miss_count, eviction_count);
   return 0;
}


