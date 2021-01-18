//#include <stdio.h>
//#include <stdlib.h>
//#include "Person.h"
//#include "Meeting.h"
//#include "SpreaderDetector.h"
//#include <assert.h>
//
//#define READ "r"
////files
//#define FIRST_PEOPLE "ex3test/first-people.txt"
//#define FIRST_MEET "ex3test/first-meeting.txt"
//#define SECOND_PEOPLE "ex3test/sec-people.txt"
//#define SECOND_MEET "ex3test/sec-meeting.txt"
//#define FIRST_OUTPUT "ex3test/first_output.txt"
//#define MANY_PERSON "ex3test/many-people.txt"
//#define MANY_MEETING "ex3test/many-meetings.txt"
//#define MANY_OUTPUT "ex3test/many-output.txt"
//#define JUNK_OUTPUT "ex3test/junk_output.txt"
//#define EDGE_PEOPLE "ex3test/edge-people.txt"
//#define EDGE_MEET "ex3test/edge-meeting.txt"
//#define EDGE_OUTPUT "ex3test/edge-output.txt"
//
//
//
//
//
////messages
//#define PERSON_BASIC_PASS "pass basic test for Person module\n"
//#define MEETING_BASIC_PASS "pass basic test for Meeting module\n"
//#define SPREAD_BASIC_PASS "pass basic test for SpreadDetector module\n"
//#define SPREAD_BASIC_FILE "pass pass basic test for SpreadDetector module with file\n"
//#define PASS_ONE_PERSON_MSG "passed test with one person and no meetings\n"
//#define PASS_MANY_MSG "passed test with many people and meetings\n"
//#define PASS_ARG_PROBLEMS_MSG "passed test with problems in functions arguments\n"
//#define PASS_EDGE_CASES_NO_FILE_MSG "passed test with edge cases without file\n"
//#define PASS_EDGE_CASES_WITH_FILE_MSG "passed test with edge cases with file\n"
//#define PASS_ALL_TEST_MSG "******************\npassed all tests\n******************\n"
//
//
//Person *FindPersonById(SpreaderDetector *spr, IdT id){
//  Person *person = NULL;
//  for (size_t i = 0; i < spr->people_size; ++i){
//    if (spr->people[i]->id == id){
//      person = spr->people[i];
//      break;
//    }
//  }
//  return person;
//}
//
//
//void CheckPersonBasic(){
//  Person *p1 = PersonAlloc(444444444, "one", 45, 0);
//  Person *p2 = PersonAlloc(444444444, "two", 20, 0);
//  Person *p3 = PersonAlloc(111111111, "misho", 9, 1);
//  Person *p4 = PersonAlloc(222222222, "misho", 9, 1);
//  assert(PersonCompareByAge(p3, p4) == 0 && "compare age of 3 and 4");
//  assert(PersonCompareByAge(p1, p2) == -1 && "compare age of 1 and 2");
//  assert(PersonCompareByAge(p2, p1) == 1 && "compare age of 2 and 1");
//  assert(PersonCompareByInfectionRate(p1, p2) == 0 && "compare infection of 1 and 2");
//  assert(PersonCompareByInfectionRate(p1, p3) == 1 && "compare infection of 1 and 3");
//  assert(PersonCompareByInfectionRate(p3, p1) == -1 && "compare infection of 3 and 1");
//  assert(PersonCompareById(p1, p2) == 0 && "compare id of 1 and 2");
//  assert(PersonCompareById(p3, p4) == -1 && "compare id of 3 and 4");
//  assert(PersonCompareById(p4, p3) == 1 && "compare id of 4 and 3");
//  assert(PersonCompareByName(p3, p4) == 0 && "compare name of 3 and 4");
//  assert(PersonCompareByName(p2, p3) == 1 && "compare name of 2 and 3");
//  assert(PersonCompareByName(p3, p2) == -1 && "compare name of 3 and 2");
//  PersonFree(&p1);
//  PersonFree(&p2);
//  PersonFree(&p3);
//  PersonFree(&p4);
//  printf(PERSON_BASIC_PASS);
//}
//
//
//void CheckMeetingBasic(){
//  Person *p1 = PersonAlloc(444444444, "one", 45, 0);
//  Person *p2 = PersonAlloc(444444444, "two", 20, 0);
//  Person *p3 = PersonAlloc(111111111, "misho", 9, 1);
//  Meeting *p1_p2 = MeetingAlloc(p1, p2, 4.5, 6.3);
//  Meeting *p1_p3 = MeetingAlloc(p1, p3, 6.0, 3.2);
//  assert(MeetingGetPerson(NULL, 2) == NULL && "check when pointer is not valid");
//  assert(MeetingGetPerson(p1_p2, 0) == NULL && "check when pointer is not valid");
//  assert(MeetingGetPerson(p1_p2, 3) == NULL && "check when index out of range");
//  assert(MeetingGetPerson(p1_p2, 2) == p2 && "check getting person 2");
//  assert(MeetingGetPerson(p1_p3, 1) == p1 && "check when getting person 1");
//  PersonFree(&p1);
//  PersonFree(&p2);
//  PersonFree(&p3);
//  MeetingFree(&p1_p2);
//  MeetingFree(&p1_p3);
//  printf(MEETING_BASIC_PASS);
//}
//
//
//void CheckSpredBasic(){
//  SpreaderDetector *spr = SpreaderDetectorAlloc();
//  Person *p1 = PersonAlloc(306356321, "Ofira", 53, 0);
//  Person *p2 = PersonAlloc(201336708, "Berko", 50, 0);
//  SpreaderDetectorAddPerson(spr, p1);
//  SpreaderDetectorAddPerson(spr, p2);
//  Meeting *meeting = MeetingAlloc(p1, p2, 10.1, 10);
//  SpreaderDetectorAddMeeting(spr, meeting);
//  assert(p1->meetings[0] == meeting);
//  PersonFree(&p1);
//  PersonFree(&p2);
//  MeetingFree(&meeting);
//  SpreaderDetectorFree(&spr);
//  printf(SPREAD_BASIC_PASS);
//}
//
//
//void CheckSpreWithFile(){
//  SpreaderDetector *spr = SpreaderDetectorAlloc();
//  SpreaderDetectorReadPeopleFile(spr, FIRST_PEOPLE);
//  SpreaderDetectorReadMeetingsFile(spr, FIRST_MEET);
//  SpreaderDetectorCalculateInfectionChances(spr);
//  SpreaderDetectorPrintRecommendTreatmentToAll(spr,FIRST_OUTPUT);
//  for (size_t k_i = 0; k_i < spr->meeting_size; ++k_i) {
//    MeetingFree(&spr->meetings[k_i]);
//  }
//  for (size_t k_j = 0; k_j < spr->people_size; ++k_j) {
//    PersonFree(&spr->people[k_j]);
//  }
//  SpreaderDetectorFree(&spr);
//  printf(SPREAD_BASIC_FILE);
//}
//
//
//void CheckSpreOnePerson(){
//  SpreaderDetector *spr = SpreaderDetectorAlloc();
//  SpreaderDetectorReadPeopleFile(spr, SECOND_PEOPLE);
//  SpreaderDetectorReadMeetingsFile(spr, SECOND_MEET);
//  SpreaderDetectorCalculateInfectionChances(spr);
//  assert(spr->people_size == 1);
//  assert(spr->meeting_size == 0);
//  assert(spr->people[0]->meetings_capacity == PERSON_INITIAL_SIZE);
//  assert(spr->people[0]->num_of_meetings == 0);
//  assert(spr->people[0]->infection_rate == 1.0);
//  for (size_t k_i = 0; k_i < spr->meeting_size; ++k_i) {
//    MeetingFree(&spr->meetings[k_i]);
//  }
//  for (size_t k_j = 0; k_j < spr->people_size; ++k_j) {
//    PersonFree(&spr->people[k_j]);
//  }
//  SpreaderDetectorFree(&spr);
//  printf(PASS_ONE_PERSON_MSG);
//}
//
//
//int LineInFile(char *file){
//  int counter = 0;
//  FILE *f = fopen(file, READ);
//  char line[MAX_LEN_OF_LINE] = {'\0'};
//  while (fgets(line, MAX_LEN_OF_LINE, f)){
//    counter++;
//  }
//  fclose(f);
//  return counter;
//}
//
//
//void CheckMany(){
//  SpreaderDetector *spr = SpreaderDetectorAlloc();
//  SpreaderDetectorReadPeopleFile(spr, MANY_PERSON);
//  SpreaderDetectorReadMeetingsFile(spr, MANY_MEETING);
//  SpreaderDetectorCalculateInfectionChances(spr);
//  SpreaderDetectorPrintRecommendTreatmentToAll(spr,MANY_OUTPUT);
//  assert(spr->meeting_size == 37);
//  assert(spr->people_size == 38);
//  assert(spr->meeting_cap == 64);
//  assert(spr->people_cap == 64);
//  assert(SpreaderDetectorGetNumOfMeetings(spr) == 37);
//  assert(SpreaderDetectorGetNumOfPeople(spr) == 38);
//  assert(LineInFile(MANY_OUTPUT) == 38);
//  Person *one = FindPersonById(spr, 111111111);
//  assert(one->num_of_meetings == 19);
//  assert(one->meetings_capacity == 32);
//  Meeting *meet = PersonGetMeetingById(one, 222222222);
//  Person *two = MeetingGetPerson(meet, 2);
//  assert(two->num_of_meetings == 5);
//  assert(two->meetings_capacity == PERSON_INITIAL_SIZE);
//  for (size_t k_i = 0; k_i < spr->meeting_size; ++k_i) {
//    MeetingFree(&spr->meetings[k_i]);
//  }
//  for (size_t k_j = 0; k_j < spr->people_size; ++k_j) {
//    PersonFree(&spr->people[k_j]);
//  }
//  SpreaderDetectorFree(&spr);
//  printf(PASS_MANY_MSG);
//}
//
//
//void CheckEdgeCaseWithoutFile(){
//  SpreaderDetector *spr = SpreaderDetectorAlloc();
//  Person *p1 = PersonAlloc(306356321, "Ofira", 53, 1);
//  Person *p2 = PersonAlloc(201336708, "Berko", 50, 0);
//  Meeting *meeting = MeetingAlloc(p1, p2, 10.1, 10);
//  assert(SpreaderDetectorGetInfectionRateById(spr, 111111111) == -1 && "problem when person not exist\n");
//  assert(SpreaderDetectorPrintRecommendTreatmentToAll(spr, JUNK_OUTPUT) == 1 && "problem when there is no people\n");
//  SpreaderDetectorCalculateInfectionChances(spr);
//  SpreaderDetectorAddPerson(spr, p2);
//  SpreaderDetectorCalculateInfectionChances(spr);
//  assert(SpreaderDetectorPrintRecommendTreatmentToAll(spr, JUNK_OUTPUT) == 1 && "problem when there is no one sick\n");
//  assert(SpreaderDetectorAddMeeting(spr, meeting) == 0 && "problem when one of the people doesnt exist\n");
//  assert(PersonGetMeetingById(p1, 333333333) == 0 && "problem when one of the people doesnt exist\n");
//  PersonFree(&p1);
//  PersonFree(&p2);
//  MeetingFree(&meeting);
//  SpreaderDetectorFree(&spr);
//  printf(PASS_EDGE_CASES_NO_FILE_MSG);
//}
//
//
//void CheckEdgeCaseWithFile(){
//  SpreaderDetector *spr = SpreaderDetectorAlloc();
//  SpreaderDetectorReadPeopleFile(spr, EDGE_PEOPLE);
//  SpreaderDetectorReadMeetingsFile(spr, EDGE_MEET);
//  assert(spr->people_size == 3 && "problem in adding people\n");
//  assert(spr->meeting_size == 1 && "problem in adding meetings\n");
//  SpreaderDetectorCalculateInfectionChances(spr);
//  SpreaderDetectorPrintRecommendTreatmentToAll(spr, EDGE_OUTPUT);
//  assert(LineInFile(EDGE_OUTPUT) == 3 && "problem in calculate and print all people\n");
//  Person *sick = FindPersonById(spr, 222222222);
//  assert(sick->num_of_meetings == 1);
//  assert(sick->meetings_capacity == PERSON_INITIAL_SIZE);
//  Person *misho = FindPersonById(spr, 111111111);
//  assert(misho->num_of_meetings == 0);
//  for (size_t k_i = 0; k_i < spr->meeting_size; ++k_i) {
//    MeetingFree(&spr->meetings[k_i]);
//  }
//  for (size_t k_j = 0; k_j < spr->people_size; ++k_j) {
//    PersonFree(&spr->people[k_j]);
//  }
//  SpreaderDetectorFree(&spr);
//  printf(PASS_EDGE_CASES_WITH_FILE_MSG);
//}
//
//void CheckWithWrongArg(){
//  Person *p = PersonAlloc(111111111, "misho", 9, 1);
//  Person *p1 = PersonAlloc(306356321, "Ofira", 53, 0);
//  Person *p2 = PersonAlloc(201336708, "Berko", 50, 0);
//  Meeting *meeting = MeetingAlloc(p1, p2, 10.1, 10);
//  Meeting *non = PersonGetMeetingById(p, 0);
//  assert(non == NULL && "problem when get id that doesnt have 9 digits\n");
//  non = PersonGetMeetingById(NULL, 111111111);
//  assert(non == NULL && "problem when get NULL as pointer to person\n");
//  assert(MeetingGetPerson(meeting, 8) == NULL && "problem when index is out of range\n");
//  assert(MeetingGetPerson(NULL, 1) == NULL && "problem when pointer is NULL\n");
//  SpreaderDetector *detect = SpreaderDetectorAlloc();
//  assert(SpreaderDetectorAddPerson(NULL, p) == 0 && "problem when pointer is NULL\n");
//  assert(SpreaderDetectorAddPerson(detect, NULL) == 0 && "problem when pointer is NULL\n");
//  assert(SpreaderDetectorAddMeeting(NULL, meeting) == 0 && "problem when pointer is NULL\n");
//  assert(SpreaderDetectorAddMeeting(detect, NULL) == 0 && "problem when pointer is NULL\n");
//  SpreaderDetectorReadMeetingsFile(NULL, FIRST_MEET);
//  SpreaderDetectorReadPeopleFile(NULL, FIRST_PEOPLE);
//  assert(SpreaderDetectorGetInfectionRateById(NULL, 111111111) == -1 && "problem when pointer is NULL\n");
//  assert(SpreaderDetectorGetInfectionRateById(detect, 1) == -1 && "problem when get id that doesnt have 9 digits\n");
//  SpreaderDetectorCalculateInfectionChances(NULL);
//  assert(SpreaderDetectorPrintRecommendTreatmentToAll(NULL, JUNK_OUTPUT) == 0 && "problem when pointer is NULL\n");
//  assert(SpreaderDetectorGetNumOfPeople(NULL) == 0 && "problem when pointer is NULL\n");
//  assert(SpreaderDetectorGetNumOfMeetings(NULL) == 0 && "problem when pointer is NULL\n");
//  Person *person[1] = {0};
//  PersonFree(NULL);
//  PersonFree(person);
//  Meeting *meet[1] = {0};
//  MeetingFree(meet);
//  MeetingFree(NULL);
//  SpreaderDetector *spr[1] = {0};
//  SpreaderDetectorFree(spr);
//  SpreaderDetectorFree(NULL);
//  PersonFree(&p);
//  PersonFree(&p1);
//  PersonFree(&p2);
//  MeetingFree(&meeting);
//  SpreaderDetectorFree(&detect);
//  printf(PASS_ARG_PROBLEMS_MSG);
//}
//
//
//int main() {
//  CheckPersonBasic();
//  CheckMeetingBasic();
//  CheckSpredBasic();
//  CheckSpreWithFile();
//  CheckSpreOnePerson();
//  CheckMany();
//  CheckEdgeCaseWithoutFile();
//  CheckEdgeCaseWithFile();
//  CheckWithWrongArg();
//  printf(PASS_ALL_TEST_MSG);
//  return 0;
//}



#include "SpreaderDetector.h"

#include <stdio.h>
int statistic(int Grades[], int size, float *avg, int *max) {
    int number_student = 0, current_max = 0, sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += Grades[i];
        if (Grades[i] > current_max) {
            current_max = Grades[i];
        }
    }
    for (int j = 0; j < size; ++j) {
        if (Grades[j] == current_max) {
            number_student++;
        }
    }
    *avg = (float) sum / (float) size;
    *max = current_max;
    return number_student;
}


int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    int Grades[100], size = 0, num, *max ;
    float *avg;
    while (fscanf(file, "%d", &num) > 0) {
        Grades[size++] = num;
    }
    fclose(file);
    int number_student = statistic(Grades, size, avg, max);
    printf("Average = %.2f \n", *avg);
    printf("Maximum grade = %d \n",*max);
    printf("Number of Maximum grades = %d \n",number_student);
    return 0;
}