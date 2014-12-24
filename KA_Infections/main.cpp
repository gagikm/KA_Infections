//
//  main.cpp
//  KA_Infections
//
//  Created by Gagik Movsisyan on 12/20/14.
//  Copyright (c) 2014 Gagik Movsisyan. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;


struct user{
    user(double version, string username){cur_version = version; name = username;}
    string name;
    double cur_version;          //user's current version of KA
    
    vector <user*> students;     //users coached by this user
    vector <user*> coaches;      //users who coach this user
};


void total_infection(double new_version, user *victim){
    
    
    //Deploy new version to this user
    victim->cur_version = new_version;
    cout<<"[TI]Infected "<<victim->name<<" with v"<<new_version<<".\n";
    
    //Call total infection on each uninfected student
    for(int i=0; i<victim->students.size(); i++){
        if(new_version > victim->students[i]->cur_version)
            total_infection(new_version, victim->students[i]);
    }
    
    //Call total infection on each uninfected coach
    for(int i=0; i<victim->coaches.size(); i++){
        if (new_version > victim->coaches[i]->cur_version)
            total_infection(new_version, victim->coaches[i]);
    }
    return;
}



void limited_infection(double new_version, int num_users, vector<user*> user_db){
    
    vector <user*> copy;
    copy = user_db;
    
    while(num_users != 0){
        
        int best = 0;
        
        //find first uninfected user
        while( copy[best] == NULL || copy[best]->cur_version >= new_version){
            if(best < copy.size()-1)
                best++;
            if(best == copy.size()-1 && copy[best]->cur_version >= new_version){
                cout<<"[LI]There are not enough users to infect.\n";
                return;//exit(EXIT_FAILURE);
            }
        }
        
        //if there are no uninfected users left, exit
        if(copy[best] == NULL || copy[best]->cur_version >= new_version)
            return;
        
        //find uninfected user with least number of students
        for(int i=0; i<copy.size(); i++){
            if(copy[i]!=NULL &&
               copy[i]->cur_version<new_version &&
               copy[i]->students.size()<copy[best]->students.size())
                best = i;
        }
        
        
        if (num_users == 1){
            //deploy to the user with smallest number of students
            if(new_version > copy[best]->cur_version){
                copy[best]->cur_version=new_version;
                cout<<"[LI]Infected "<<copy[best]->name<<" with v"<<new_version<<".\n";                num_users--;
            }
            return;
        }
        
        //find user with number of students closest to our goal, but not more
        for (int i=0; i<copy.size(); i++){
            if(copy[i] != NULL){
                double i_class_size = copy[i]->students.size();
                double i_class_fit = i_class_size / (num_users - 1);
                
                double best_class_size = copy[best]->students.size();
                double best_class_fit = best_class_size  / (num_users - 1);
                
                if(i_class_fit <= 1 && i_class_fit > best_class_fit){
                    best = i;
                }
            }
        }
        
        //deploy new version to best available user
        if(new_version > copy[best]->cur_version){
            copy[best]->cur_version = new_version;
            num_users--;
            cout<<"[LI]Infected "<<copy[best]->name<<" with v"<<new_version<<".\n";
        }
        
        //deploy new version to best user's uninfected students
        for(int i=0; i<copy[best]->students.size(); i++){
            if(num_users == 0){
                cout<<"[LI]Done with "<<copy[best]->name<<"'s students. \nNot all students were infected.";
                return;
            }
            if(new_version > copy[best]->students[i]->cur_version){
                cout<<"[LI]Infected "<<copy[best]->name<<"'s student, "<<copy[best]->students[i]->name<<" with v"<<new_version<<".\n";
                copy[best]->students[i]->cur_version = new_version;
                num_users--;
            }
        }
        copy[best] = NULL;
        
        
    }
    
    return;
    
    
}

//auxiliarry function to assign students to teachers
void assign(user* student, user* coach){
    coach->students.push_back(student);
    student->coaches.push_back(coach);
}


int main(int argc, const char * argv[]) {
    
    //create users
    user *Andy      = new user(1.0, "Andy");
    user *Bernard   = new user(1.0, "Bernard");
    user *Creed     = new user(1.0, "Creed");
    user *Dwight    = new user(1.0, "Dwight");
    user *Ellen     = new user(1.0, "Ellen");
    user *Fiona     = new user(1.0, "Fiona");
    user *Gabe      = new user(1.0, "Gabe");
    user *Holly     = new user(1.0, "Holly");
    user *Isabel    = new user(1.0, "Isabel");
    user *Jim       = new user(1.0, "Jim");
    user *Kevin     = new user(1.0, "Kevin");
    user *Lucy      = new user(1.0, "Lucy");
    user *Michael   = new user(1.0, "Michael");
    user *Natalie   = new user(1.0, "Natalie");
    user *Oscar     = new user(1.0, "Oscar");
    user *Pam       = new user(1.0, "Pam");
    user *Qin       = new user(1.0, "Qin");
    user *Ryan      = new user(1.0, "Ryan");
    user *Schrute   = new user(1.0, "Schrute");
    user *Toby      = new user(1.0, "Toby");
    user *Uji       = new user(1.0, "Uji");
    user *Varam     = new user(1.0, "Varam");
    user *White     = new user(1.0, "White");
    
    //assign students to teachers
    assign(Andy, Michael);
    assign(Bernard, Michael);
    assign(Creed, Michael);
    assign(Dwight, Michael);
    assign(Ellen, Michael);
    assign(Holly, Michael);
    assign(Jim, Michael);
    assign(Kevin, Michael);
    assign(Pam, Michael);
    assign(Ryan, Michael);
    
    assign(Fiona, Jim);
    assign(Gabe, Jim);
    assign(Isabel, Jim);
    assign(Lucy, Jim);
    
    assign(Natalie, Pam);
    assign(Oscar, Pam);
    assign(Qin, Pam);
    assign(Schrute, Pam);
    
    assign(Uji, Dwight);
    assign(Varam, Dwight);
    assign(White, Dwight);
    assign(Toby, Dwight);
    
    //create network of users
    vector <user*> KhanAcademyUsers;
    KhanAcademyUsers.push_back(Michael);
    KhanAcademyUsers.push_back(Andy);
    KhanAcademyUsers.push_back(Bernard);
    KhanAcademyUsers.push_back(Creed);
    KhanAcademyUsers.push_back(Dwight);
    KhanAcademyUsers.push_back(Ellen);
    KhanAcademyUsers.push_back(Fiona);
    KhanAcademyUsers.push_back(Gabe);
    KhanAcademyUsers.push_back(Holly);
    KhanAcademyUsers.push_back(Isabel);
    KhanAcademyUsers.push_back(Jim);
    KhanAcademyUsers.push_back(Kevin);
    KhanAcademyUsers.push_back(Lucy);
    KhanAcademyUsers.push_back(Michael);
    KhanAcademyUsers.push_back(Natalie);
    KhanAcademyUsers.push_back(Oscar);
    KhanAcademyUsers.push_back(Pam);
    KhanAcademyUsers.push_back(Qin);
    KhanAcademyUsers.push_back(Ryan);
    KhanAcademyUsers.push_back(Schrute);
    KhanAcademyUsers.push_back(Toby);
    KhanAcademyUsers.push_back(Uji);
    KhanAcademyUsers.push_back(Varam);
    KhanAcademyUsers.push_back(White);
    
    
    //test limited_infection and total_infection

    total_infection(1.3, Michael);
    limited_infection(1.4, 10, KhanAcademyUsers);
    cout<<'\n';
    for (int i=0; i<KhanAcademyUsers.size(); i++) {
        cout<<KhanAcademyUsers[i]->name<<": v"<<KhanAcademyUsers[i]->cur_version<<'\n';
    }
    
}
