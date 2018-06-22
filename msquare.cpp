#include <iostream>
#include <list>
#include <fstream>
#include <string.h>
#include <assert.h>

const int MAX_TRANS = 512;

using namespace std;

int setbits(int destination, int source, int at, int numbits)
{
    int ones = ((1<<(numbits))-1)<<at;
    return (ones|destination)^((~source<<at)&ones);
}

int fact(int n)
{
    int a=1;
    for(int i=1; i <=n; i++) a *= i;
    return a;
}

struct transformation_list
{
	//use two bits per transformation
	unsigned char data[MAX_TRANS/4];
	int nTrans;
	transformation_list()
	{
		nTrans = 0;
	}
	void add(int t)
	{
		data[t/4] |= data[t/4] | (t & 3) << (t%4)*2;
	}
	int get(int n)
	{
		return (data[n/4] >> (n % 4)*2) & 3;
	}
	void printlist(ofstream & fout)
	{
		fout << nTrans;
		for(int i=0;i<nTrans; i++)
		{
			if (i%60 == 0) fout << endl;
			fout << (get(i) + "A");
		}
		fout << endl;
	}
};


class msquare
{
public:
    char sq[2][4];
	transformation_list tlist;
    msquare(list<int> &l)
    {
        list<int>::iterator li = l.begin();
        for(int i=0; i < 2; i++)
            for(int j=0;j<4; j++, li++)
                sq[i][j] = *li;
    }
	void print(ofstream & fout)
	{
		 for(int i=0; i < 2; i++)
		 {
            for(int j=0;j<4; j++)
                fout << sq[i][j] << " ";
			fout << endl;
		 }
	}

	//will store the sq in a four byte datum,
	template <typename I>
	I compress()
	{
		I acc = 0;
		assert(sizeof(I) == 4);
		for(int i=0;i<2;i++)
			for(int j=0;j<4; j++)
				acc = acc << 3 | sq[i][j]; 
	}

    //get a number representing the state of the msquare
    //there are only 40,320 states in the current configuration

	unsigned short get_factoriadic_digit()
	{
		bool useddigit[8];
		int factor = 5040, remaining=8;
		unsigned short acc = 0;
		for(int i=0;i<2; i++)
			for(int j=0;j<4; j++)
			{
				int l=0;
				for(int ii=0;ii<sq[i][j]; ii++)
				{
					assert(ii <= 7);
					if(!useddigit[ii]) l++;
				}
				assert(l > 0);
				assert(l <= 8);
				useddigit[l-1] = true;
				acc += l*factor;
				factor /= remaining;
				remaining -=1;
			}
		assert(acc < 40320);
		return acc;
	}
    
	 msquare transform(int op)
	{
		msquare r(*this);
		memcpy(r.sq[0],this->sq[0], 4);
		memcpy(r.sq[1],this->sq[1], 4);
	
		switch(op)
		{
		case 0:
			for(int j=0;j<4; j++)
			{
				r.sq[0][j];
				int temp = sq[0][j];
				sq[0][j] = sq[1][j];
				sq[1][j] = temp;
			}
			break;
		case 1:
			for(int i=0; i<2; i++)
			{
				int temp = sq[i][3];
				for(int j=3;j>0; j--)
					sq[i][j] = sq[i][j-1];
				sq[i][0] = temp;
			}
			break;
		case 2:
			int temp = sq[0][1];
			sq[0][1] = sq[1][1];
			sq[1][1] = sq[1][2];
			sq[1][2] = sq[0][2];
			sq[0][2] = temp;
			break;
		}
		r.tlist.add(op);
		return r;
	}

};

int main()
{
    list<int> ans_list;
    ifstream fin;
    ofstream fout;
    fin.open("msquare.in");
    fout.open("msquare.out");
    int n;
    fout << "0" << endl;
    for(int i=0;i<8; i++){
        fin >> n;
        ans_list.insert(ans_list.end(), n);
    }
    
    msquare target(ans_list);
	unsigned short ans_state = target.get_factoriadic_digit();
    cout << ans_state;
	bool seen[40320];
	list<msquare> q;

	fout << "1" << endl;

	while(true)
	{
		msquare sq = q.front();
		q.pop_front();
		unsigned short crnt_state =sq.get_factoriadic_digit();
		sq.print(fout);
		fout << "current state: " << crnt_state << endl;
		if(seen[crnt_state])
		{
			//we have a cycle to a previous state, ignore
			fout << "already seen" << endl;
			continue;
		}

		else if(crnt_state == ans_state)
		{
			fout << "result found" << endl;
			sq.tlist.printlist(fout);
			break;
		}

		else
		{
			fout <<"applying transfomations"<< endl;
			seen[sq.get_factoriadic_digit()] = true;
			for(int i=0;i<3; i++)
			{
				q.insert(q.end(), sq.transform(i));
			}
		}
	}

    
    return 0;
    
}
