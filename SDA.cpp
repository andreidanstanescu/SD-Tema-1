#include<iostream>
#include<random>
#include<fstream>
#include<algorithm>
#include<time.h>
#include<iomanip>
#include<bits/stdc++.h>
using namespace std;


void Counting(int arr[],int n,int dim,int exp)
{
    int count[dim+1]={0};
    int* out=new int[n];
    for(int i=0;i<n;i++)
        count[(arr[i]/exp)%10]++;
    for(int i=1;i<=dim;i++)
        count[i]+=count[i-1];
    for(int i=n-1;i>=0;i--)
    {
        out[count[(arr[i]/exp)%10]-1]=arr[i];
        count[(arr[i]/exp)%10]--;
    }
    for(int i=0;i<n;i++)
        arr[i]=out[i];
}



void Radix(int arr[],int n)
{
    int minv=INT_MAX;
    for(int i=0;i<n;i++)
        if(arr[i]<minv)
        minv=arr[i];
    int dim=INT_MIN;
    for(int i=0;i<n;i++)
        if(arr[i]>dim)
        dim=arr[i];
    for(int i=0;i<n;i++)
        arr[i]-=minv;
    for(int exp=1;dim/exp>0;exp*=10)
        Counting(arr,n,9,exp);
    for(int i=0;i<n;i++)
        arr[i]+=minv;
}


void Counting_256(int arr[],int n,int bucket)
{
    vector<int> count(256);
    int* output=new int[n];

    for(int i = 0; i < n; i++)
        count[(arr[i]>>(8*bucket))&255]++;

    for(int i = 1; i < 256; i++)
           count[i] += count[i-1];

    for(int i = n-1; i >= 0; i--)
    {
         output[ count[(arr[i]>>(8*bucket))&255] -1 ] = arr[i];
              count[(arr[i]>>(8*bucket))&255]--;
    }

    for(int i=0; i < n; i++)
            arr[i] = output[i];

}


void Radix_256(int arr[],int n)
{
    //am adaugat si val minima ca sa mearga si pe negative
    int minv=INT_MAX;
    for(int i=0;i<n;i++)
        if(arr[i]<minv)
        minv=arr[i];
    for(int i=0;i<n;i++)
        arr[i]-=minv;
    int nr_bytes=sizeof(arr[0]);
    for(int bucket=0;bucket<nr_bytes;bucket++)
        Counting_256(arr,n,bucket);
    for(int i=0;i<n;i++)
        arr[i]+=minv;
}

//counting sort si pentru numere negative
void countSort(vector <int>& arr,int v[])
{
    int max = *max_element(arr.begin(), arr.end());
    int min = *min_element(arr.begin(), arr.end());
    int range = max - min + 1;

    vector<int> count(range);
    vector<int> output(arr.size());
    for(int i = 0; i < arr.size(); i++)
        count[arr[i]-min]++;

    for(int i = 1; i < count.size(); i++)
           count[i] += count[i-1];

    for(int i = arr.size()-1; i >= 0; i--)
    {
         output[ count[arr[i]-min] -1 ] = arr[i];
              count[arr[i]-min]--;
    }

    for(int i=0; i < arr.size(); i++)
            v[i] = output[i];
}


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    //dimensiunea din stanga si din dreapta
    int ls = m - l + 1;
    int ld =  r - m;

    int *L=new int[ls];
    int *R=new int[ld];

    for (i = 0; i < ls; i++)
        L[i] = arr[l + i];
    for (j = 0; j < ld; j++)
        R[j] = arr[m+1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < ls && j < ld)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < ls)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < ld)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

void bubble(int arr[],int n)
{
   int i, j;
   bool bule;
   for (i = 0; i < n-1; i++)
   {
     bule = false;
     for (j = 0; j < n-i-1; j++)
     {
        if (arr[j] > arr[j+1])
        {
           swap(&arr[j], &arr[j+1]);
           bule = true;
        }
     }

     // IF no two elements were swapped by inner loop, then break
     if (bule == false)
        break;
   }
}


int MedianOfThree(int arr[],int left,int right)
{
    int mid = (left + right)/2;
    if (arr[right] < arr[left])
        swap(&arr[left],&arr[right]);
    if (arr[mid] < arr[left])
        swap(&arr[left],&arr[mid]);
    if (arr[right] < arr[mid])
        swap(&arr[right],&arr[mid]);
    return mid;
}

void quicksort(int G[],int st,int dr)
{
    //nu e stabil
    int i,j;
    int x,y;
    x=G[MedianOfThree(G,st,dr)];
    i=st;
    j=dr;
    do
    {
        while(i<dr && G[i]<x) i++;
        while(j>st && G[j]>x) j--;
        if(i<=j)
        {   y=G[i];
            G[i]=G[j];
            G[j]=y;
            i++;
            j--;
        }
    } while(i<=j);
    if(st<=j) quicksort(G,st,j);
    if(i<=dr) quicksort(G,i,dr);

}


void CombHeap(int i,int k,int G[])     //O(log n)
{
    int tata=i,fiu=i*2;
    int v=G[i];
    while(fiu<=k)
    {
        if(fiu<k)
            if(G[fiu]<G[fiu+1]) fiu++;
        if(v<G[fiu])
        {
            G[tata]=G[fiu];
            tata=fiu;
            fiu=fiu*2;
        }
        else fiu=k+1;
    }
    G[tata]=v;
}



void create_heap(int G[],int n)
{
    for(int i=n/2;i;i--)
        CombHeap(i,n,G);

}


void heapsort(int G[],int n)
{
    int aux;
    create_heap(G,n);
    for(int i=n;i>1;i--)
    {
        aux=G[1];
        G[1]=G[i];
        G[i]=aux;
        CombHeap(1,i-1,G);
    }

}

int comp(const void* a,const void* b)
{
    return (*(int*)a-*(int*)b);
}


//cu skip lists
class nod{
public:
    int inf;
    nod** adr;
    nod(int val,int nivel)
    {
        this->inf=val;
        this->adr=new nod*[nivel+1];
        for(int i=0;i<=nivel;i++)
            this->adr[i]=NULL;
    };
};

int random_level(int n)
{
    int nivel=1;
    srand((unsigned)time(0));
    while(rand()%100<50 && nivel<n)
        nivel++;
    return nivel;
}

void Insert(int x,nod* head,int &lev_max,int n)
{
    nod* curr=head;
    nod* replace[lev_max+2];
    memset(replace, NULL, sizeof(nod*)*(lev_max+2));
    for(int i=lev_max;i>=0;i--)
    {
        while(curr->adr[i]!=NULL && curr->adr[i]->inf<x)
            curr=curr->adr[i];
        replace[i]=curr;
    }

    //unde il inserez efectiv in lista mare:
    nod* de_inserat=curr->adr[0];
    //if(de_inserat==NULL || de_inserat->inf!=x){
        //ii determin nivelul randomizat
        int new_level=random_level(n);
        if(new_level>lev_max)
        {
            new_level=lev_max+1;
            lev_max++;
            replace[lev_max]=head;
        }
        nod* nou=new nod(x,new_level);
        for(int i=new_level;i>=0;i--)
        {
            nou->adr[i]=replace[i]->adr[i];
            replace[i]->adr[i]=nou;
        }

    }



void skip_list_sort(int arr[],int n)
{
    nod* head=new nod(0,n);
    int lev_max=0;
    for(int i=0;i<n;i++)
        Insert(arr[i],head,lev_max,n);
    for(int i=0;i<n;i++)
    {
        arr[i]=head->adr[0]->inf;
        head=head->adr[0];
    }
}


void copiere_initial(int a[],int n,int v[])
{
    for(int i=0;i<n;i++)
        v[i]=a[i];
}

void copiere_initial1(int a[],int n,int v[])
{
    for(int i=0;i<n;i++)
        v[i+1]=a[i];
}

bool verificare_sortat(int arr[],int n,int v[])
{
    //stim ca au acelasi numar de elemente(n)
    //deci verificam daca au si aceleasi elemente
    unordered_set<int> s;
    for(int i=0;i<n;i++)
        s.insert(arr[i]);
    for(int i=0;i<n;i++)
    if(!s.count(v[i]))
    return 0;
    for(int i=0;i<n-1;i++)
        if(v[i]>v[i+1])
        return 0;
    return 1;

}


int main()
{
    default_random_engine generator;
    clock_t inc,sf;
    time_t start,end;
    int n,m,ms,t,nr=0;
    ifstream fin("generare.in");
    ofstream fout("vector.out");
    fin>>t;
    srand((unsigned)time(NULL));
    while(t--)
    {
        fout<<"test "<<++nr<<endl;
        fin>>n>>m;
    int maxv;
    int *a=new int[n];
    int *v=new int[n];
    if(nr==1 )
        ms=-m;
    else ms=0;
    uniform_int_distribution<int> distribution(ms, m);
    for(int i=0;i<n;i++)
        {
        a[i]=distribution(generator);
        //sau a[i]=rand()%m+1;
        //fin>>a[i];
        if(a[i]>maxv)
            maxv=a[i];
        v[i]=a[i];
        }

    //nu e bun la m foarte mare deoarece range-ul creat este prea mare sa fie dimensiune de vector in countSort
    if(n<1e5)
    {vector<int> arr(v,v+n);
    time(&start);
    countSort(arr,v);
    time(&end);
    fout<<"Counting Sort:\n";
    fout<<fixed<<(double)(end-start)<<setprecision(10)<<endl;
    fout<<"este sortat: "<<verificare_sortat(a,n,v)<<endl;
    }

    copiere_initial(a,n,v);
    inc=clock();
    Radix(v,n);
    sf=clock();
    fout<<"Radix in baza 10:\n";
    fout<<fixed<<(double)(sf-inc)/double(CLOCKS_PER_SEC)<<setprecision(10)<<endl;
    fout<<"este sortat: "<<verificare_sortat(a,n,v)<<endl;

    //merge si pe negative
    time(&start);
    copiere_initial(a,n,v);
    Radix_256(v,n);
    time(&end);
    fout<<"Radix in baza 256:\n";
    fout<<fixed<<(double)(end-start)<<setprecision(10)<<endl;
    fout<<"este sortat: "<<verificare_sortat(a,n,v)<<endl;

    if(n<1e5)
    {copiere_initial(a,n,v);
    time(&start);
    bubble(v,n);
    time(&end);
    fout<<"Bubble:\n";
    fout<<fixed<<(double)(end-start)<<setprecision(10)<<endl;
    fout<<"este sortat: "<<verificare_sortat(a,n,v)<<endl;
    }

    copiere_initial(a,n,v);
    time(&start);
    mergeSort(v,0,n-1);
    time(&end);
    fout<<"Merge:\n";
    fout<<fixed<<(double)(end-start)<<setprecision(10)<<endl;
    fout<<"este sortat: "<<verificare_sortat(a,n,v)<<endl;

    copiere_initial(a,n,v);
    time(&start);
    quicksort(v,0,n-1);
    time(&end);
    fout<<"Quick Sort:\n";
    fout<<fixed<<(double)(end-start)<<setprecision(10)<<endl;
    fout<<"este sortat: "<<verificare_sortat(a,n,v)<<endl;

    int* v1=new int[n+1];
    copiere_initial1(a,n,v1);
    time(&start);
    heapsort(v1,n);
    for(int i=0;i<n;i++)
        v[i]=v1[i+1];
    time(&end);
    fout<<"HeapSort:\n";
    fout<<fixed<<(double)(end-start)<<setprecision(10)<<endl;
    fout<<"este sortat: "<<verificare_sortat(a,n,v)<<endl;

    copiere_initial(a,n,v);
    time(&start);
    qsort(v,n,sizeof(int),comp);
    time(&end);
    fout<<"qsort(stl):\n";
    fout<<fixed<<(double)(end-start)<<setprecision(10)<<endl;
    fout<<"este sortat: "<<verificare_sortat(a,n,v)<<endl;

    if(nr==5)
    {
    //din cauza multor referinte pentru valori f mari nu este utila implementare mea de skip lists (pentru n f mare)
    copiere_initial(a,n,v);
    time(&start);
    skip_list_sort(v,n);
    time(&end);
    fout<<"Skip Lists Sort:\n";
    fout<<fixed<<(double)(end-start)<<setprecision(10)<<endl;
    fout<<"este sortat: "<<verificare_sortat(a,n,v)<<endl;
    }
    //o afisare
    /*if(nr==1)
    {for(int i=0;i<n;i++)
        fout<<v[i]<<' ';
        fout.close();
    }*/
}
fin.close();
fout.close();
}
