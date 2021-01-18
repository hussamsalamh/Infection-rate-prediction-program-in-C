#include "SpreaderDetector.h"

#define MAX_CHAR 256
#define BASE 10
#define ID_LENGTH 9


/**
 * Allocates (dynamically) a spreader detector with no meetings and
 * no people.
 * @return pointer to dynamically allocated SpreaderDetector struct.
 * @if_fails returns NULL.
 */
SpreaderDetector *SpreaderDetectorAlloc() {
    SpreaderDetector *spr = (SpreaderDetector *) malloc(sizeof(SpreaderDetector));
    spr->people_cap = SPREADER_DETECTOR_INITIAL_SIZE;
    spr->meeting_cap = SPREADER_DETECTOR_INITIAL_SIZE;
    spr->people_size = 0;
    spr->meeting_size = 0;
    spr->people = (Person **) malloc(sizeof(Person *) * SPREADER_DETECTOR_INITIAL_SIZE);
    spr->meetings = (Meeting **) malloc(sizeof(Meeting *) * SPREADER_DETECTOR_INITIAL_SIZE);
    return spr;
}

/**
 *  Frees the given spreader detector.
 * @param p_spreader_detector pointer to spreader detector pointer
 * should be freed.
 */
void SpreaderDetectorFree(SpreaderDetector **p_spreader_detector) {
    if (p_spreader_detector == NULL || *p_spreader_detector == NULL) {
        return;
    }
    free((*p_spreader_detector)->meetings);
    (*p_spreader_detector)->meetings = NULL;
    free((*p_spreader_detector)->people);
    (*p_spreader_detector)->people = NULL;
    free((*p_spreader_detector));
}

Person *FindPersonById(SpreaderDetector *spreaderDetector, IdT id) {
    for (size_t i = 0; i < spreaderDetector->people_size; ++i) {
        if (spreaderDetector->people[i]->id == id) {
            return spreaderDetector->people[i];
        }
    }
    return 0;
}

void *AddMeetingToPerson(Meeting *meeting, Person *person) {
    if (person == NULL || meeting == NULL) {
        return 0;
    }
    person->meetings[person->num_of_meetings++] = meeting;
    if (person->num_of_meetings == person->meetings_capacity) {
        person->meetings_capacity *= PERSON_GROWTH_FACTOR;
        person->meetings = realloc(person->meetings, sizeof(Meeting) * person->meetings_capacity);
        if (person->meetings == NULL) {
        }
    }
    return 0;
}

/**
 * Adds the given person to the spreader detector.
 * Important - each person is unique (compare by id).
 * @param spreader_detector the spreader detector we wants to add the person to.
 * @param person the person we wants to add to the spreader detector.
 * @return 1 if the person was added successfully, 0 otherwise.
 * @if_fails returns 0.
 */
int SpreaderDetectorAddPerson(SpreaderDetector *spreader_detector, Person *person) {
    if (spreader_detector == NULL || person == NULL) {
        return 0;
    }
    for (size_t i = 0; i < spreader_detector->people_size; ++i) {
        if (spreader_detector->people[i]->id == person->id) {
            return 0;
        }
    }
    spreader_detector->people[spreader_detector->people_size++] = person;
    if (spreader_detector->people_size == spreader_detector->people_cap) {
        spreader_detector->people_cap = spreader_detector->people_cap * SPREADER_DETECTOR_GROWTH_FACTOR;
        (*spreader_detector).people = realloc(spreader_detector->people,
                                              sizeof(Person *) * spreader_detector->people_cap);
        if (spreader_detector->people == NULL) {
            SpreaderDetectorFree((SpreaderDetector **) spreader_detector);
            return 0;
        }
    }
    return 1;
}

/**
 *  Adds the given meeting to the spreader detector.
 * Important - the people in the meeting should exist in the spreader detector.
 * @param spreader_detector the spreader detector we wants to add the meeting to.
 * @param meeting the meeting we wants to add to the spreader detector.
 * @return 1 if the meeting was added successfully, 0 otherwise.
 * @if_fails returns 0.
 */
int SpreaderDetectorAddMeeting(SpreaderDetector *spreader_detector, Meeting *meeting) {
    if (spreader_detector == NULL || meeting == NULL) {
        return 0;
    }
    if (meeting->person_2 == NULL || meeting->person_1 == NULL) {
        return 0;
    }
    Person *a = FindPersonById(spreader_detector, meeting->person_1->id);
    Person *b = FindPersonById(spreader_detector, meeting->person_2->id);
    if (a == 0 || b == 0 || a == b) {
        return 0;
    }
    spreader_detector->meetings[spreader_detector->meeting_size++] = meeting;
    AddMeetingToPerson(meeting, meeting->person_1);
    if (spreader_detector->meeting_size == spreader_detector->meeting_cap) {
        spreader_detector->meeting_cap *= SPREADER_DETECTOR_GROWTH_FACTOR;
        spreader_detector->meetings = realloc(spreader_detector->meetings,
                                              sizeof(Meeting *) * spreader_detector->meeting_cap);
        if (spreader_detector->meetings == NULL) {
            SpreaderDetectorFree((SpreaderDetector **) spreader_detector);
            return 0;
        }
    }
    return 1;
}

/**
 * This function convert the char * to number
 * @param num the number
 * @return the number
 */
size_t ConvertToNum(char *num) {
    char *ptr;
    size_t ret = strtol(num, &ptr, BASE);
    return ret;
}

/**
 * This function is to set person from the line
 * @param line the line
 * @return Pointer to the person
 */
Person *SetPersonFromLine(char *line) {
    char *token = strtok(line, " \r\n");
    char *name = NULL;
    size_t age = 0, id = 0;
    int is_sick = 0, i = 0;
    while (token) {
        switch (i) {
            case 0:
                name = token;
                break;
            case 1:
                id = ConvertToNum(token);
                break;
            case 2:
                age = ConvertToNum(token);
                break;
            case 3:
                is_sick = 1;
                break;
        }
        ++i;
        token = strtok(NULL, " \r\n");
    }
    return PersonAlloc(id, name, age, is_sick);
}


/**
 *  * This function reads the file of the people, parses to file into person objects,
 * and inserts it to the spreader detector.
 * @param spreader_detector the spreader detector we wants to read the people into.
 * @param path the path to the people file.
 */
void SpreaderDetectorReadPeopleFile(SpreaderDetector *spreader_detector, const char *path) {
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL || spreader_detector == NULL) {
        return;
    }
    char line[MAX_CHAR];
    while (fgets(line, MAX_CHAR, fptr) != NULL) {
        Person *person;
        person = SetPersonFromLine(line);
        SpreaderDetectorAddPerson(spreader_detector, person);
    }
    fclose(fptr);
}

/**
 * This function set a meeting from the line
 * @param line the line
 * @param spreader_detector the spreader detector
 * @return the meeting
 */
Meeting *SetMeetingFromLine(char *line, SpreaderDetector *spreader_detector) {
    line = strtok(line, "\r\n");
    line = strtok(line, "\n");
    char *token = strtok(line, " ");
    size_t lst[4];
    int i = 0;
    while (token) {
        lst[i++] = ConvertToNum(token);
        token = strtok(NULL, " ");
    }
    Person *person_1 = FindPersonById(spreader_detector, lst[0]);
    Person *person_2 = FindPersonById(spreader_detector, lst[1]);
    Meeting *meeting = MeetingAlloc(person_1, person_2, lst[3], lst[2]);
    return meeting;
}

/**
 * This function reads the file of the meeting, parses to file into meetings,
 * and inserts it to the spreader detector.
 * @param spreader_detector the spreader detector we wants to read the meetings into.
 * @param path the path to the meetings file.
 */
void SpreaderDetectorReadMeetingsFile(SpreaderDetector *spreader_detector, const char *path) {
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL || spreader_detector == NULL) {
        return;
    }
    char line[MAX_CHAR];
    while (fgets(line, MAX_CHAR, fptr) != NULL) {
        Meeting *meeting = SetMeetingFromLine(line, spreader_detector);
        SpreaderDetectorAddMeeting(spreader_detector, meeting);
    }
    fclose(fptr);
}


/**
 * This function check if the length of the number is 9 (the length of the if)
 * @param integer
 * @return the length
 */
int CheckLength(int integer) {
    int len;
    for (len = 1; integer /= BASE; len++);
    return len;
}

/**
 * * Returns the infection rate of the person with the given id.
 * @param spreader_detector the spreader detector contains the person.
 * @param id the id of the person we are looking for.
 * @return the infection rate of the person, if not person exists -
 * returns -1.
 * @if_fails returns -1.
 */
double SpreaderDetectorGetInfectionRateById(SpreaderDetector *spreader_detector, IdT id) {
    if (spreader_detector == NULL || CheckLength(id) != ID_LENGTH) {
        return -1;
    }
    for (size_t i = 0; i < spreader_detector->people_size; ++i) {
        if (spreader_detector->people[i]->id == id) {
            return spreader_detector->people[i]->infection_rate;
        }
    }
    return -1;
}

/**
 *  * Returns the number of people which are in the spreader detector.
 * @param spreader_detector the spreader detector object.
 * @return the number of people.
 * @if_fails return 0.
 */
size_t SpreaderDetectorGetNumOfPeople(SpreaderDetector *spreader_detector) {
    if (spreader_detector == NULL) {
        return 0;
    }
    return spreader_detector->people_size;
}


/**
 * Returns the number of meetings which are in the spreader detector.
 * @param spreader_detector the spreader detector object.
 * @return the number of meetings.
 * @if_fails return 0.
 */
size_t SpreaderDetectorGetNumOfMeetings(SpreaderDetector *spreader_detector) {
    if (spreader_detector == NULL) {
        return 0;
    }
    return spreader_detector->meeting_size;
}


/**
 * The aim of this function is to help to calculate the infection of the people
 * @param person person
 */
void SpreaderDetectorCalculateInfectionChancesHelper(Person *person) {
    if (person->num_of_meetings == 0) {
        return;
    }
    for (size_t i = 0; i < person->num_of_meetings; ++i) {
        if (person->meetings[i]->person_2 != person) {
            Person *person_2 = MeetingGetPerson(person->meetings[i], 2);
            person_2->infection_rate = person->infection_rate * (person->meetings[i]->measure * MIN_DISTANCE)
                                       / (person->meetings[i]->distance * MAX_MEASURE);
            if (person_2->age > AGE_THRESHOLD) {
                person_2->infection_rate += INFECTION_RATE_ADDITION_DUE_TO_AGE;
            }
            SpreaderDetectorCalculateInfectionChancesHelper(person_2);
        }
    }
}

/**
 * This function runs the algorithm which calculates the infection rates of the people.
 * When this algorithm ends, the user should be able to use the function
 * SpreaderDetectorGetInfectionRateById and get the infection rate of each person.
 * @param spreader_detector a spreader_detector.
 */
void SpreaderDetectorCalculateInfectionChances(SpreaderDetector *spreader_detector) {
    if (spreader_detector == NULL) {
        return;
    }
    for (size_t i = 0; i < spreader_detector->people_size; ++i) {
        if (spreader_detector->people[i]->is_sick == 1) {
            SpreaderDetectorCalculateInfectionChancesHelper(spreader_detector->people[i]);
        }
    }
}

/**
 * This function used to sort the people according to there infcation rate
 * @param spreaderDetector spreader Detector
 * @return
 */
void *SortLst(SpreaderDetector *spreaderDetector) {
    for (size_t i = 0; i < spreaderDetector->people_size; ++i) {
        Person *temp = NULL;
        for (size_t j = 0; j < spreaderDetector->people_size; ++j) {
            if (spreaderDetector->people[i]->infection_rate > spreaderDetector->people[j]->infection_rate) {
                temp = spreaderDetector->people[j];
                spreaderDetector->people[j] = spreaderDetector->people[i];
                spreaderDetector->people[i] = temp;
            }
        }
    }
    return 0;
}

/**
 * Gets the recommendation for treatment for all people based on the parameters above,
 * and prints it to the given file path.
 * @param spreader_detector the spreader detector contains the person.
 * @param file_path the path to the output file.
 * @return returns 1 if printed successfully, 0 otherwise.
 * @if_fails return 0.
 */
int SpreaderDetectorPrintRecommendTreatmentToAll(SpreaderDetector *spreader_detector, const char *file_path) {
    FILE *fp = fopen(file_path, "w");
    if (spreader_detector == NULL || fp == NULL) {
        return 0;
    }
    SortLst(spreader_detector);
    for (size_t i = 0; i < spreader_detector->people_size; ++i) {
        char *treatment = " ";
        if (spreader_detector->people[i]->infection_rate > MEDICAL_SUPERVISION_THRESHOLD) {
            treatment = MEDICAL_SUPERVISION_THRESHOLD_MSG;
        } else if (spreader_detector->people[i]->infection_rate > REGULAR_QUARANTINE_THRESHOLD) {
            treatment = REGULAR_QUARANTINE_MSG;
        } else {
            treatment = CLEAN_MSG;
        }
        fprintf(fp, treatment, spreader_detector->people[i]->name, spreader_detector->people[i]->id,
                spreader_detector->people[i]->age,
                spreader_detector->people[i]->infection_rate);
    }
    fclose(fp);
    return 1;
}
