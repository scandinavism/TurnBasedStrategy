#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "irrlicht.h"
#include "DGameMap.h"


struct PathNode
{
    int x;
    int y;

    int cost;
};

int distance(PathNode start,PathNode finish)
{
    int startx = start.x;
    int startz = start.y - (start.x- (start.x%2))/2;
    int starty = -startx-startz;


    int finishx = finish.x ;
    int finishz = finish.y - (finish.x - (finish.x%2))/2;
    int finishy = -finishx-finishz;

    return (abs(startx-finishx)+abs(starty-finishy)+abs(startz-finishz))/2;
}

class Queue
{
public:
    Queue* prev;
    Queue* next;

    int priority;
    PathNode stored_node;
    int traveled_so_far;

    Queue* camefrom;

    Queue()
    {
        prev = 0;
        next = 0;
        priority = -1;
        traveled_so_far = 0;

        stored_node.x=-1;
        stored_node.y=-1;
        camefrom = 0;
        //MASTER NODE WILL ALWAYS HAVE -1 PRIORITY AND -1 VALUES FOR STORED NODE!
    }

    int length(PathNode finish)
    {
        Queue* current = this;
        int i = 0;


        while (current->next!=0)
        {

            current = current->next;

            i++;
        }

        return i;
    }

    void print()
    {
        Queue* current = this;
        int i = 0;

        printf ("ALL QUEUE SO FAR:\n");
        while (current->next!=0)
        {

            current = current->next;
            printf ("NN: %d X:%d Y:%d PRIORITY:%d TRAVELED:%d\n",i,current->stored_node.x,current->stored_node.y,current->priority,current->traveled_so_far);
            i++;
        }
        printf("=-=-=-=-=-=-=-=-=-=-\n\n\n");

    }

    void add(PathNode node, int priority, int traveled, Queue* _camefrom)
    {
        Queue* current = this;

        while (current->next!=0 && priority>current->priority)
        {
            current=current->next;
        }

        // now we know the first node with priority more than desired
        // so we need to use classic "add before" method, if:

        Queue *added = new Queue();

        /*added->prev = current;
        added->next = current->next;
        if (added->next!=0) added->next->prev = added;
        current->next = added;*/

        if (priority<=current->priority)
        {
        added->next = current;
        added->prev = current->prev;
        if (added->prev!=0) added->prev->next = added;
        current->prev = added;
        }
        else
        {
            current->next = added;
            added->prev= current;
            added->next = 0;
        }




        added->priority = priority;
        added->stored_node = node;
        added->traveled_so_far = traveled;
        added->camefrom = _camefrom;


    }

    void deletenext()
    {

        if (next!=0)
        {
            Queue* _next = next;
            if (next->next!=0) next->next->prev = this;
            next = next->next;

        }

    }

    void deleteall()
    {
        Queue* current = last();
        while (current->prev!=0)
        {

            current = current->prev;
            delete current->next;
        }

    }

    Queue* NodeWithXY(int x,int y)
    {
        Queue* current = this;
        bool found = false;

        while (current->next!=0)
        {
            current = current->next;
            found = ((current->stored_node.x== x) && (current->stored_node.y ==y));
            if (found) break;
        }

        if (found)
            return current;
        else
            return 0;

    }

    Queue* first()
    {

        return next;
        //this method should be called from masternode;
    }

    Queue* last()
    {
        Queue* current = this;
        while (current->next!=0) current=current->next;
        return current;

        // we need it to delete all from last to first
    }



};

 core::array<vector2d<s32> > A_Star (PathNode start, PathNode finish, TileInfo** TileMap)
{
    Queue* OpenQueue = new Queue();
    Queue* ClosedQueue = new Queue();

    OpenQueue->add(start,distance(start,finish),0,0);
    //OpenQueue->print();

    Queue* current;
    current= OpenQueue->first();

    while (current!=0 && ClosedQueue->NodeWithXY(finish.x,finish.y)==0)
    {

        ClosedQueue->add(current->stored_node,current->priority,current->traveled_so_far,current->camefrom);
        OpenQueue->deletenext();

        PathNode NodeToAdd;
        int heuristic_distance;
        int traveled;


        NodeToAdd.x = UNbrI(current->stored_node.x,current->stored_node.y);
        NodeToAdd.y = UNbrJ(current->stored_node.x,current->stored_node.y);
        if (current->stored_node.y!=(J_SIZE-1))

        NodeToAdd.cost = getBaseMovementCost(TileMap[NodeToAdd.x][NodeToAdd.y].TerrainType);
        // heightmap[NodeToAdd.x][NodeToAdd.y]==2?1:5; // replace with smth TileInfo[NodeToAdd.x][NodeToAdd.y].Movementcost;
        else
        NodeToAdd.cost = INFINITE;

        heuristic_distance = distance(NodeToAdd,finish);
        traveled = current->traveled_so_far+NodeToAdd.cost;

        //consider moving this to function
        if (ClosedQueue->NodeWithXY(NodeToAdd.x,NodeToAdd.y)==0)
        {

            Queue* Existing= OpenQueue->NodeWithXY(NodeToAdd.x,NodeToAdd.y);
            if (Existing==0)
            {

                OpenQueue->add(NodeToAdd,heuristic_distance+traveled,traveled,current);

            }
            else
            {
                if (Existing->priority>heuristic_distance+traveled)
                {
                    Existing->priority=heuristic_distance+traveled;
                    Existing->traveled_so_far=traveled;
                    Existing->camefrom = current;
                }
            }
        }
        //end function


        NodeToAdd.x = URNbrI(current->stored_node.x,current->stored_node.y);
        NodeToAdd.y = URNbrJ(current->stored_node.x,current->stored_node.y);

        if (current->stored_node.y!=(J_SIZE-1))
            NodeToAdd.cost = getBaseMovementCost(TileMap[NodeToAdd.x][NodeToAdd.y].TerrainType);
            // heightmap[NodeToAdd.x][NodeToAdd.y]==2?1:5; // replace with smth TileInfo[NodeToAdd.x][NodeToAdd.y].Movementcost;
           else
        NodeToAdd.cost = INFINITE;


        heuristic_distance = distance(NodeToAdd,finish);
        traveled = current->traveled_so_far+NodeToAdd.cost;

        //consider moving this to function
        if (ClosedQueue->NodeWithXY(NodeToAdd.x,NodeToAdd.y)==0)
        {

            Queue* Existing= OpenQueue->NodeWithXY(NodeToAdd.x,NodeToAdd.y);

            if (Existing==0)
            {

                OpenQueue->add(NodeToAdd,heuristic_distance+traveled,traveled,current);

            }
            else
            {

                if (Existing->priority>heuristic_distance+traveled)
                {
                    Existing->priority=heuristic_distance+traveled;
                    Existing->traveled_so_far=traveled;
                    Existing->camefrom = current;

                }
            }
        }
        //end function



       NodeToAdd.x = ULNbrI(current->stored_node.x,current->stored_node.y);
        NodeToAdd.y = ULNbrJ(current->stored_node.x,current->stored_node.y);

        if (current->stored_node.y!=(J_SIZE-1))
            NodeToAdd.cost = getBaseMovementCost(TileMap[NodeToAdd.x][NodeToAdd.y].TerrainType);
            // heightmap[NodeToAdd.x][NodeToAdd.y]==2?1:5; // replace with smth TileInfo[NodeToAdd.x][NodeToAdd.y].Movementcost;
           else
        NodeToAdd.cost = INFINITE;

        heuristic_distance = distance(NodeToAdd,finish);
        traveled = current->traveled_so_far+NodeToAdd.cost;

        //consider moving this to function
        if (ClosedQueue->NodeWithXY(NodeToAdd.x,NodeToAdd.y)==0)
        {
            Queue* Existing= OpenQueue->NodeWithXY(NodeToAdd.x,NodeToAdd.y);
            if (Existing==0)
            {
                OpenQueue->add(NodeToAdd,heuristic_distance+traveled,traveled,current);
            }
            else
            {
                if (Existing->priority>heuristic_distance+traveled)
                {
                    Existing->priority=heuristic_distance+traveled;
                    Existing->traveled_so_far=traveled;
                    Existing->camefrom = current;
                }
            }
        }
        //end function



        NodeToAdd.x = LNbrI(current->stored_node.x,current->stored_node.y);
        NodeToAdd.y = LNbrJ(current->stored_node.x,current->stored_node.y);
        if (current->stored_node.y!=(0))

            NodeToAdd.cost = getBaseMovementCost(TileMap[NodeToAdd.x][NodeToAdd.y].TerrainType);
            // heightmap[NodeToAdd.x][NodeToAdd.y]==2?1:5; // replace with smth TileInfo[NodeToAdd.x][NodeToAdd.y].Movementcost;
        else
        NodeToAdd.cost = INFINITE;

        heuristic_distance = distance(NodeToAdd,finish);
        traveled = current->traveled_so_far+NodeToAdd.cost;

        //consider moving this to function
        if (ClosedQueue->NodeWithXY(NodeToAdd.x,NodeToAdd.y)==0)
        {
            Queue* Existing= OpenQueue->NodeWithXY(NodeToAdd.x,NodeToAdd.y);
            if (Existing==0)
            {
                OpenQueue->add(NodeToAdd,heuristic_distance+traveled,traveled,current);
            }
            else
            {
                if (Existing->priority>heuristic_distance+traveled)
                {
                    Existing->priority=heuristic_distance+traveled;
                    Existing->traveled_so_far=traveled;
                    Existing->camefrom = current;
                }
            }
        }
        //end function



        NodeToAdd.x = LLNbrI(current->stored_node.x,current->stored_node.y);
        NodeToAdd.y = LLNbrJ(current->stored_node.x,current->stored_node.y);
        if (current->stored_node.y!=(0))

            NodeToAdd.cost = getBaseMovementCost(TileMap[NodeToAdd.x][NodeToAdd.y].TerrainType);
            // heightmap[NodeToAdd.x][NodeToAdd.y]==2?1:5; // replace with smth TileInfo[NodeToAdd.x][NodeToAdd.y].Movementcost;
        else
        NodeToAdd.cost = INFINITE;

        heuristic_distance = distance(NodeToAdd,finish);
        traveled = current->traveled_so_far+NodeToAdd.cost;

        //consider moving this to function
        if (ClosedQueue->NodeWithXY(NodeToAdd.x,NodeToAdd.y)==0)
        {
            Queue* Existing= OpenQueue->NodeWithXY(NodeToAdd.x,NodeToAdd.y);
            if (Existing==0)
            {
                OpenQueue->add(NodeToAdd,heuristic_distance+traveled,traveled,current);
            }
            else
            {
                if (Existing->priority>heuristic_distance+traveled)
                {
                    Existing->priority=heuristic_distance+traveled;
                    Existing->traveled_so_far=traveled;
                    Existing->camefrom = current;
                }
            }
        }
        //end function



        NodeToAdd.x = LRNbrI(current->stored_node.x,current->stored_node.y);
        NodeToAdd.y = LRNbrJ(current->stored_node.x,current->stored_node.y);

        if (current->stored_node.y!=(0))

            NodeToAdd.cost = getBaseMovementCost(TileMap[NodeToAdd.x][NodeToAdd.y].TerrainType);
            // heightmap[NodeToAdd.x][NodeToAdd.y]==2?1:5; // replace with smth TileInfo[NodeToAdd.x][NodeToAdd.y].Movementcost;
        else
        NodeToAdd.cost = INFINITE;

        heuristic_distance = distance(NodeToAdd,finish);
        traveled = current->traveled_so_far+NodeToAdd.cost;

        //consider moving this to function
        if (ClosedQueue->NodeWithXY(NodeToAdd.x,NodeToAdd.y)==0)
        {
            Queue* Existing= OpenQueue->NodeWithXY(NodeToAdd.x,NodeToAdd.y);
            if (Existing==0)
            {
                OpenQueue->add(NodeToAdd,heuristic_distance+traveled,traveled,current);
            }
            else
            {
                if (Existing->priority>heuristic_distance+traveled)
                {
                    Existing->priority=heuristic_distance+traveled;
                    Existing->traveled_so_far=traveled;
                    Existing->camefrom = current;
                }
            }
        }
        //end function


       // printf("TOTAL ON END: %d %d %d\n",current->stored_node.x,current->stored_node.y,OpenQueue->length(finish));

     //   OpenQueue->print();


        current=OpenQueue->first();

    }

    current = ClosedQueue->NodeWithXY(finish.x,finish.y);

    core::array<vector2d<s32> > result;
    result.clear();
    result.set_used(0);

    if (current!=0)
    {
        printf("\n -==== STEPS BACKWARDS ====- \n");
    while (current->stored_node.x!=start.x || current->stored_node.y!=start.y)
    {
        printf ("X:%d Y:%d\n",current->stored_node.x,current->stored_node.y);
        result.push_back(vector2d<s32>(current->stored_node.x,current->stored_node.y));
        current=current->camefrom;
    }

    result.push_back(vector2d<s32>(current->stored_node.x,current->stored_node.y));
    }

    OpenQueue->deleteall();
    ClosedQueue->deleteall();
    delete OpenQueue;
    delete ClosedQueue;
    return result;



}





#endif // PATHFINDING_H
