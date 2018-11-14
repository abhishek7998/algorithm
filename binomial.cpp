#include<bits/stdc++.h>
using namespace std;
#define lli long long int
struct Node{
        lli key;
        Node* child;
        Node* sib;
        Node* p;
        lli d;
        Node(lli c){
            key=c;
            child=0;
            sib=0;
            p=0;
            d=0;
        }
};
void rootlist(Node* h){
        Node *z=h;
        cout<<"Root List\n";
        while(z){
                cout<<z->key<<" ";
                z=z->sib;
        }
        cout<<endl;
}
Node* link(Node* x,Node* y){
        x->p=y;
        x->sib=y->child;
        y->child=x;
        y->d= y->d +1;
        return y;
}

Node* merge(Node* h1,Node* h2){
        if(h1==0)
            return h2;
        if(h2==0)
            return h1;
        Node *s=new Node(0),*c=s;
        Node *x=h1,*y=h2;
        while(x && y){
            if(x->d <= y->d){
                s->sib=x;
                x->p=s->p;
                s=s->sib;
                x=x->sib;
            }
            else{
                s->sib=y;
                y->p=s->p;
                s=s->sib;
                y=y->sib;
            }
        }
        while(x){
                s->sib=x;
                x->p=s->p;
                s=s->sib;
                x=x->sib;
        }
        while(y){
                s->sib=y;
                y->p=s->p;
                s=s->sib;
                y=y->sib;
        }
        return c->sib;
}

Node* unite(Node* h1,Node* h2){
      Node* h=merge(h1,h2);
      if(h==0)
        return 0;
      Node* prev=0,*x=h,*n=x->sib;
      while(n){
        if((x->d != n->d) || (n->sib && n->sib->d==x->d )){
            prev=x;
            x=n;
        }
        else{
            if(x->key < n->key){
                x->sib=n->sib;
                x=link(n,x);
            }
            else{
                if(prev==0)
                    h=n;
                else
                    prev->sib=n;
                n=link(x,n);
                x=n;
            }
        }
        n=x->sib;
      }
      return h;
}

Node* insert(Node* h,lli x){
        Node* z=new Node(x);
        return unite(h,z);
}

Node* extractmin(Node* h){
        Node* m=0;
        Node* t=h;
        while(t){
                if(m==0 || m->key > t->key)
                        m=t;
                t=t->sib;
        }
        return m;
}

Node* reverse(Node* h){
    Node *t=h,*n=0,*p=0;
    while(t){
        n=t->sib;
        t->sib=p;
        t->p=0;
        p=t;
        t=n;
    }
    return p;
}

void retrieve(Node* h,lli x,Node *& z){
    if(h==0)
        return;
    if(h->key==x)
        z=h;
    retrieve(h->child,x,z);
    retrieve(h->sib,x,z);
}

void exchange(Node* x,Node* y){
        swap(x->child,y->child);
        swap(x->p,y->p);
        swap(x->d,y->d);
        swap(x->sib,y->sib);
        swap(x->key,y->key);
}

void decrease_key(Node* h,lli n,lli k){
    if(n<k)
        return;
    Node* x=0;
    retrieve(h,n,x);
    x->key=k;
    Node *y=x->p;
    while(y && x->key < y->key){
        exchange(x,y);
        x=y;
        y=x->p;
    }
}

Node* delete_min(Node* h){
    Node *m=extractmin(h);
    if(m==0)
        return h;
    Node* t=h;

    if(t->key==m->key){
        h=h->sib;
    }
    else{
        while(t->sib){
            if(t->sib->key==m->key)
                t->sib=t->sib->sib;
            else
                t=t->sib;
        }
    }
    m=m->child;
    m=reverse(m);
    return unite(h,m);

}

Node* delete_key(Node* h,lli x){
    decrease_key(h,x,LONG_LONG_MAX);
    return delete_min(h);
}

int main(){
    lli a[]={4,3,7,-1,2,6,5};
    Node* h=0;
    lli i;
    for(i=0;i<7;i++){
        h=insert(h,a[i]);
        rootlist(h);
    }
    cout<<"MIN= "<<extractmin(h)->key<<endl;
    h=delete_min(h);
    cout<<"MIN= "<<extractmin(h)->key<<endl;
    h=delete_key(h,3);
    cout<<"MIN= "<<extractmin(h)->key<<endl;

}
