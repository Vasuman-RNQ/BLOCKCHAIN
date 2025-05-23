#include<bits/stdc++.h>
using namespace std;

#define block_max_tcount 2
string type_meaning[4]={"manufacture","transport","quality_check","side_effects"};

string myhash(int n)
{
    return to_string(n);
}

class Transaction
{
public:

    //Common attributes to all type of transactions
    int product_id;
    int type;
    string date;
    string description;

    //Manufacture
    string location;
    string chemical_composition;
    //Transport
    int from_id;
    int to_id;
    //Quality Check
    bool OK_tested;
};

void print_transaction(Transaction*t)
    {
        cout<<type_meaning[t->type]<<" "<<t->product_id<<"\n";
        cout<<"Date: "<<t->date<<"\n";

        if(t->type==0)
        {
            cout<<"Location: "<<t->location<<"\n";
            cout<<"Chemical Compositon: "<<t->chemical_composition<<"\n";
        }
        else if(t->type==1)
        {
            cout<<"From: "<<t->from_id<<"\n";
            cout<<"To: "<<t->to_id<<"\n";
        }
        else if(t->type==2)
        {
            if(t->OK_tested)
                cout<<"Quality: OK\n";
            else cout<<"Quality: Not OK (CAUTION!!)\n";
        }

        if(t->description!="") cout<<"Description: "<<t->description<<"\n";
    }


class Block
{
public:

    int number;
    string prev_hash;
    string block_hash;
    string merkele_root;
    vector<Transaction*>transactions;

    string calculate_merkele_root()
    {
        return "";
    }

    string calculate_block_hash()
    {
        return "";
    }
};

class BlockChain
{
public:

    vector<Block*>blockchain;
    BlockChain()
    {
        Block* genesis_block=new Block();
        genesis_block->number=0;
        genesis_block->prev_hash="";
        genesis_block->merkele_root="";
        genesis_block->block_hash=genesis_block->calculate_block_hash();
        blockchain.push_back(genesis_block);
    }
};

void register_node(unordered_set<int>&registered_nodes, int node_id)
{
    registered_nodes.insert(node_id);
    cout<<"Node Registered successfully!\n";
}

void print_product_details(unordered_map<int,vector<Transaction*>>&productExplorer, int product_id)
{
    if(productExplorer.find(product_id)==productExplorer.end())
    {
        cout<<"Sorry! This product doesn\'t exist. Enter a valid product id.\n";
        return;
    }
    for(auto transaction:productExplorer[product_id])
        print_transaction(transaction);
}

bool validate_transaction(Transaction* t)
{
    //Write appropriate logic here
    return true;
}

int main()
{
    unordered_set<int>registered_nodes;
    queue<Transaction*>mempool;



    unordered_map<int,vector<Transaction*>>productExplorer;

    
    BlockChain supplyChain;

    while(1)
    {
        cout<<endl;
        cout<<"**-------------------------------------------------**\n";
        cout<<"Press\n r -> to Register a new Node \n t -> to Add a Transaction \n e -> to Trace or Explore a Product\n s -> to Stop the Program\n";
        cout<<"**-------------------------------------------------**\n";
        string option;
        cin>>option;

        /*
        R -> Register a new node
        T -> Transaction
                0-> Mfg
                1-> Transport
                2-> Quality Check
                3-> Side effect
        E -> Explore/Trace a product
        S -> Stop the Program and Exit
        */

        if(option=="R" or option=="r")
        {
            int node_id;
            cout<<"Enter node Id you want to register: ";
            cin>>node_id;
            register_node(registered_nodes,node_id);
        }

        else if(option=="T" or option=="t")
        {
            int transaction_type;
            cout<<"Enter the type of Transaction ";
            cout<<"(0 for Manufacturing, 1 for Transport, 2 for Quality Check and 3 for Side Effect report) : ";
            cin>>transaction_type;

            Transaction* t=new Transaction();
            t->type=transaction_type;

            if(transaction_type==0)
            {
                cout<<"Enter the following details as prompted Or write NA if not applicable.\n";

                cout<<"Product Id: ";
                cin>>t->product_id;

                cout<<"Manufacturing Date: ";
                cin>>t->date;
                cout<<"Manufacturing Unit Location: ";
                cin>>t->location;
                cout<<"Chemical Composition: ";
                cin>>t->chemical_composition;

                cout<<"Description/ Other Details: ";
                cin>>t->description;
            }
            else if(transaction_type==1)
            {
                cout<<"Enter the following details as prompted Or write NA if not applicable.\n";

                cout<<"Product Id: ";
                cin>>t->product_id;
                cout<<"Transaction Date: ";
                cin>>t->date;

                cout<<"Transported From (Node Id): ";
                cin>>t->from_id;
                cout<<"Transported To (Node Id): ";
                cin>>t->to_id;

                cout<<"Description/ Other Details: ";
                cin>>t->description;
            }
            else if(transaction_type==2)
            {
                cout<<"Enter the following details as prompted Or write NA if not applicable.\n";

                cout<<"Product Id: ";
                cin>>t->product_id;

                cout<<"Quality Check Date: ";
                cin>>t->date;
                cout<<"Quality OK? (1 for YES, 0 for NO): ";
                cin>>t->OK_tested;

                cout<<"Description: ";
                cin>>t->description;
            }
            else if(transaction_type==3)
            {
                cout<<"Enter the following details as prompted Or write NA if not applicable.\n";

                cout<<"Product Id: ";
                cin>>t->product_id;
                cout<<"Side Effect Reported Date: ";
                cin>>t->date;
                cout<<"Description: ";
                cin>>t->description;
            }
            else
            {
                cout<<"Invalid Transaction Type.\n";
                continue;
            }

            if(validate_transaction(t))
                mempool.push(t);
            else
                cout<<"Invalid Transaction. Try Again.\n";
        }

        else if(option=="E" or option=="e")
        {
            int product_id;
            cout<<"Enter Product Id: ";
            cin>>product_id;
            print_product_details(productExplorer,product_id);
        }

        else if(option=="S" or option=="s")
        {
            break;
        }

        else
        {
            cout<<"Please Enter a valid option.\n";
        }

        if(mempool.size()>=block_max_tcount)
        {
            cout<<"Adding a new block to Blockchain\n";

            Block* b=new Block();
            while(!mempool.empty())
            {
                b->transactions.push_back(mempool.front());
                mempool.pop();
            }

            b->number=supplyChain.blockchain.size();
            b->merkele_root=b->calculate_merkele_root();
            b->prev_hash=supplyChain.blockchain[b->number-1]->block_hash;
            b->block_hash=b->calculate_block_hash();

            supplyChain.blockchain.push_back(b);

            for(auto transaction: b->transactions)
            {
                int product_id=transaction->product_id;
                if(productExplorer.count(product_id))
                    productExplorer[product_id].push_back(transaction);
                else
                    productExplorer[product_id]={transaction};
            }

            /*PROPOSE A NEW BLOCK
                1. ADD SOME TRANSACTIONS
                2. CALCULATE MERKLE ROOT
                3. POPULATE PREV_HASH
                4. CALCULATE BLOCK_HASH
             MINING, CONSORTIUM AND REWARD MECHANISM - 2 OPTIONS
                1. CHOOSE A RANDOM ONE, USE PBFT/RAFT, NO REWARD
                2. PROOF OF WORK, NO CONSORTIUM REQUIRED, GIVE SOME REWARD POINTS
             DOCUMENTATION
             DEBUGGING AND TESTING
            */
        }
    }

    return 0;
}
