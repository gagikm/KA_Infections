KA-Infections
=============
Gagik Movsisyan   |
December 2014   |
Written in C++  |

<b>User Model<b>

Each user of our program has a name, a version number, a list of the user’s students, and a list of the user’s coaches. When a new user is created (someone signs up for Khan Academy), they are assigned a name and the version number of the current site they are using.

Notes:

1.	A higher version number signifies a newer version of the site. 
2.  Infecting a user means updating them to a newer version of the site.
3.	We have access to a list of all users.

<b>Total Infection<b>

void total_infection(double new_version, user* victim)

The total infection function takes in the version number of the new deployment and a pointer to the user being infected (the “victim”).

First, we deploy the new version to the victim, then we move on to the users in its network. We recursively call this function on each of the victim’s students and each of the victim’s coaches. Before we make this recursive call on a user, we check to make sure that the user has not already been updated to the new version. 


<b>Limited Infection (Exact) <b>

void limited_infection(double new_version, int num_users, vector<user*> users)

The limited infection function takes in the version number of the new deployment, the number of users we would like to infect, and a list of users. The third parameter allows us to run the infection on all users or a subgroup of users.

The goal of this function is to infect the desired amount of users while still allowing all users in a classroom to use the same version whenever possible. This function will infect exactly the number of users we want as long as that number is not more than the number of users in our list.

The function looks through the given list of users and finds the user who has a number of students closest to, but not more than, the number of users we want to infect (minus 1 for the teacher). We infect each of the user’s students with the new version, and we decrement the number of users left to infect by one with each new infection. We repeat this process, ignoring users that are already infected, until we reach our desired number of infections.  If the number of users we want to infect is larger than the size of our user list, the function returns with exit code 1 to indicate that there are not enough users to infect.


<b>Example of Limited Infection

Alvin has 10 students. Allen has 15 students. Ani has 2 students.  Let's assume that all students have no students of their own and are coached by only one teacher.

Infect 30 users using Limited Infection.<br>
Allen and his students add up to 16 users, which is the closest we can get to thirty using one class. After Allen and his students are infected, there are 14 users left to infect. Alvin and his students make 11 users while Ani and her students make up three users. We infect Alvin and his students and we are left with three users to infect. We infect Ani and her students and meet our goal of infecting 30 students. This is a case that worked out perfectly, but it does not usually go this way.

<italics>Infect 6 students using limited infection.</italics><br>
Since Allen and Alvin both have more students than we want to infect, we leave them alone to attempt to avoid messing with the version consistency in their classrooms. Ani and her students make up three users, so we infect them and we are left with three more users to infect. Unfortunately, there is no way we can avoid classroom inconsistency in this case, but we still try to minimize the damage. We look for a user who has the least number of students and we infect that user. Then, we infect that user's students until we reach our goal or run out of uninfected students for that user. In the latter case, we repeat the process on the next user with the smallest number of students. In this example, all users except for Ani, Alvin, and Allen have zero students, so three of these uninfected users will be infected.

<b>Testing</b><br>
In the main.cpp file of this project, there are test cases in the main function. When the function is called, messages are displayed to show which users got infected.


