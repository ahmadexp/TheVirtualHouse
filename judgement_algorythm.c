#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define streetlevel 2
#define house_low_x 17
#define house_high_x 32
#define house_low_z 17
#define house_high_z 32
void find_player_tile(double player_position[],int player_tile[]);
int player_in_a_room(int player_tile[]);
void make_boolean_array(int tile[],bool boolean_array[]);
int judgement(bool player_room_array[],bool target_room_array[],bool judgement_array[]);

int main (){
	//target room is always the doorway tile

	bool target_room_array[4];
	bool player_room_array[4];
	bool judgement_array[3];

	int target_room_tile[3];
	double player_position[3];
	int player_tile[3];

	printf("Input location of target room (tile x,y,z)\n");
	scanf("%d,%d,%d",&target_room_tile[0],&target_room_tile[1],&target_room_tile[2]);
	printf("Input location of player\n");
	scanf("%lf,%lf,%lf",player_position,player_position+1,player_position+2);
	printf("stored info\n");
	//what tile is player on
	find_player_tile(player_position,player_tile);
	printf("found player tile\n");
	//is player in a room
	if(player_in_a_room(player_tile)==0)
			return 1;

	//make player_room_array
	make_boolean_array(player_tile,player_room_array);
	printf("player: %d%d%d%d",player_room_array[0],player_room_array[1],player_room_array[2],player_room_array[3]);
	//making target_room_array
	make_boolean_array(target_room_tile,target_room_array);
	printf("target: %d%d%d%d",target_room_array[0],target_room_array[1],target_room_array[2],target_room_array[3]);
	//make judgement array, print result
	if(judgement(player_room_array,target_room_array,judgement_array)==0){
		printf("Fail bro\n");
		printf("%d%d%d",judgement_array[0],judgement_array[1],judgement_array[2]);
	}
	else{
		printf("Win bro\n");
		printf("%d%d%d",judgement_array[0],judgement_array[1],judgement_array[2]);
	}


	return 0;
}

void find_player_tile(double player_position[],int player_tile[]){
	int index;

	for(index = 0; index<=2; index++){
		int x;
		x=(player_position[index]/10);	
		player_tile[index]=x;
		printf("%d: %d\n", index, player_tile[index]);//NOTE: IF YOU DONT PRINT THIS, THE PROGRAM CRASHES. WHY???
	}
}

int player_in_a_room(int player_tile[]){
	return 1;
}

void make_boolean_array(int tile[],bool boolean_array[]){//this function need only work with tiles that are doorways, ie (19or30,streetlevel+1or2,19or30),
														 //because it has previously been established that the tile is indeed a room.
	//first element
	if(tile[1]==streetlevel+1)
		boolean_array[0]=0;
	else if(tile[1]==streetlevel+2)
		boolean_array[0]=1;
	//second, third and fourth elements
	//11
	if(tile[0]==house_low_x+2){
		if(tile[2]>house_low_z+((house_high_z-house_low_z)/2))//if past halfway accross house
			boolean_array[3]=0;//left
		else
			boolean_array[3]=1;//right
		boolean_array[1]=1;
		boolean_array[2]=1;
	}
	//01
	if(tile[0]==house_high_x-2){
		if(tile[2]>house_low_z+((house_high_z-house_low_z)/2))
			boolean_array[3]=1;
		else
			boolean_array[3]=0;
		boolean_array[1]=0;
		boolean_array[2]=1;
	}
	//10
	if(tile[2]==house_high_z-2){
		if(tile[0]>house_low_x+((house_high_x-house_low_x)/2))
			boolean_array[3]=0;
		else
			boolean_array[3]=1;
		boolean_array[1]=1;
		boolean_array[2]=0;
	}
	//00
	if(tile[2]==house_low_z+2){
		if(tile[0]>house_low_x+((house_high_x-house_low_x)/2))
			boolean_array[3]=1;
		else
			boolean_array[3]=0;
		boolean_array[1]=0;
		boolean_array[2]=0;
	}
}

int judgement(bool player_room_array[],bool target_room_array[],bool judgement_array[]){
	if(player_room_array[0]==target_room_array[0])
		judgement_array[0]=true;
	else
		judgement_array[0]=false;
	
	if((player_room_array[1]==target_room_array[1])&&(player_room_array[2]==target_room_array[2]))
		judgement_array[1]=true;
	else
		judgement_array[1]=false;

	if(player_room_array[3]==target_room_array[3])
		judgement_array[2]=true;
	else
		judgement_array[2]=false;

	bool correct_room=true;
	for(int x=0;x<=2;x++){
		if(judgement_array[x]==false)
			correct_room=false;
	}

	return correct_room;
}
