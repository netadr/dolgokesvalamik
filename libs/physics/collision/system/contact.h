#ifndef _contact_h_
#define _contact_h_

#include "constraint.h"
#include "math/vec3.h"
#include "physics/system/body.h"

#define MAX_CONTACTNUM_PER_BODYPAIR 4
#define CONTACTBUFFER_SIZE 8

struct one_contact
{
	vec3 rel_pos[2];
	float cached_lambda;
};

struct contact_t:public constraint_t
{
    one_contact contactarray[CONTACTBUFFER_SIZE];
    vec3 normal;
    contact_t* prev,*next;

    char contact_count;
    int group_index;

    contact_t(body_t* i_body1, body_t* i_body2);
    ~contact_t();

    void add_contact(const vec3 relpos[][2], int contact_count, const vec3& normal_body1);
};




MLINLINE contact_t::contact_t(body_t* i_body1, body_t* i_body2):
constraint_t(i_body1,i_body2)
{
    //befuzzuk a ket test kontakt-listajaba
    this->body[0]->contacts.push_front(this->edge);
    this->body[1]->contacts.push_front(this->edge+1);
    this->contact_count=0;

    for (int n=0; n<CONTACTBUFFER_SIZE; ++n)
    	this->contactarray[n].cached_lambda=0;
}

MLINLINE contact_t::~contact_t()
{
    //kifuzzuk a ket test kontakt-listajabol
    this->body[0]->contacts.erase(this->edge);
    this->body[1]->contacts.erase(this->edge+1);
/*
    if (this->edge[0].prev)
        this->edge[0].prev->next=this->edge[0].next;

    if (this->edge[0].prev)
        this->edge[0].prev->next=this->edge[0].next;

    if (this->body[0]->contacts=this->edge+0)
        this->body[0]->contacts=this->body[0]->contacts->next;

    if (this->edge[1].prev)
        this->edge[1].prev->next=this->edge[1].next;

    if (this->edge[1].prev)
        this->edge[1].prev->next=this->edge[1].next;

    if (this->body[1]->contacts=this->edge+1)
        this->body[1]->contacts=this->body[1]->contacts->next;
*/
}

#endif//_contact_h_
