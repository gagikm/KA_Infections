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


<b>Limited Infection<b>

void limited_infection(double new_version, int num_users, vector<user*> users)

The limited infection function takes in the version number of the new deployment, the number of users we would like to infect, and a list of users. The third parameter allows us to run the infection on all users or a subgroup of users.

The goal of this function is to infect the desired amount of users while still allowing all users in a classroom to use the same version whenever possible.

The function looks through the given list of users and finds the user who has a number of students closest to, but not more than, the number of users we want to infect (minus 1 for the teacher). We infect each of the user’s students with the new version, and we decrement the number of users left to infect by one with each new infection. We repeat this process, ignoring users that are already infected, until we reach our desired number of infections.  If the number of users we want to infect is larger than the size of our user list, all available users get infected and the function returns with exit code 1 to indicate that there are not enough users to infect.


<b>Example of Limited Infection

Alvin has 10 students. Allen has 15 students. Ani has 2 students.  

Infect 12 users using Limited Infection.

First, we find that Alvin has the number of students closest to 12 and not more than 12. We infect Alvin and his 10 students. This leaves one more user to be infected. Since both of the remaining users have a number of students greater than one, we choose the user with least number of students, Ani. We infect Ani and we are done. The idea is to minimize the number of students who have a coach with a different version of the site.


