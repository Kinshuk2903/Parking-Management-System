
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VEHICLES 100
#define FEE_PER_HOUR 10.0

typedef struct {
    char vehicleNo[20];
    int slotNo;
    time_t parkedTime;
} Vehicle;

int load_data(Vehicle vehicles[]) {
    FILE *file = fopen("C:\\Users\\KIIT\\Desktop\\Daa Project\\parking.txt", "r");
    if (file == NULL) {
        printf("Error opening file. Starting with an empty parking lot.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%19s %d %ld", vehicles[count].vehicleNo, &vehicles[count].slotNo, &vehicles[count].parkedTime) == 3) {
        count++;
    }
    fclose(file);
    return count;
}

int save_data(Vehicle vehicles[], int count) {
    FILE *file = fopen("parking.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving.\n");
        return 0;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %ld\n", vehicles[i].vehicleNo, vehicles[i].slotNo, vehicles[i].parkedTime);
    }
    fclose(file);
    return 1;
}

int allocate_slot(Vehicle vehicles[], int count) {
    for (int i = 0; i < MAX_VEHICLES; i++) {
        int slot_available = 1;
        for (int j = 0; j < count; j++) {
            if (vehicles[j].slotNo == i) {
                slot_available = 0;
                break;
            }
        }
        if (slot_available) {
            return i;
        }
    }
    return -1;
}

void park_vehicle(Vehicle vehicles[], int *count) {
    if (*count >= MAX_VEHICLES) {
        printf("**** PARKING IS FULL ****\n");
        return;
    }
    Vehicle new_vehicle;
    printf("Enter vehicle number: ");
    scanf("%19s", new_vehicle.vehicleNo);

    new_vehicle.slotNo = allocate_slot(vehicles, *count);
    if (new_vehicle.slotNo == -1) {
        printf("No available slots!\n");
        return;
    }

    new_vehicle.parkedTime = time(NULL);
    vehicles[*count] = new_vehicle;
    (*count)++;
    if (save_data(vehicles, *count)) {
        printf("Vehicle parked at slot number: %d\n", new_vehicle.slotNo);
    }
}

void calculate_fee(Vehicle vehicle) {
    time_t current_time = time(NULL);
    double hours_parked = difftime(current_time, vehicle.parkedTime) / 3600.0;
    double fee = hours_parked * FEE_PER_HOUR;
    printf("Vehicle No: %s, Parked for: %.2f hours, Fee: Rupees %.2f\n", vehicle.vehicleNo, hours_parked, fee);
}

void display_vehicles(Vehicle vehicles[], int count) {
    if (count == 0) {
        printf("\nNo vehicles are parked currently.\n");
        return;
    }

    printf("\nParked Vehicles:\n");
    for (int i = 0; i < count; i++) {
        printf("Slot No: %d\n", vehicles[i].slotNo);
        calculate_fee(vehicles[i]);
    }
}

void search_vehicle(Vehicle vehicles[], int count) {
    char search_no[20];
    printf("Enter vehicle number to search: ");
    scanf("%19s", search_no);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(vehicles[i].vehicleNo, search_no) == 0) {
            printf("Vehicle found!\n");
            printf("Vehicle No: %s, Slot No: %d\n", vehicles[i].vehicleNo, vehicles[i].slotNo);
            calculate_fee(vehicles[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Vehicle not found!\n");
    }
}

void unpark_vehicle(Vehicle vehicles[], int *count) {
    char search_no[20];
    printf("Enter vehicle number to unpark: ");
    scanf("%19s", search_no);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (strcmp(vehicles[i].vehicleNo, search_no) == 0) {
            printf("Vehicle found!\n");
            printf("Vehicle No: %s, Slot No: %d\n", vehicles[i].vehicleNo, vehicles[i].slotNo);
            calculate_fee(vehicles[i]);
            for (int j = i; j < *count - 1; j++) {
                vehicles[j] = vehicles[j + 1];
            }
            (*count)--;
            if (save_data(vehicles, *count)) {
                printf("Vehicle unparked successfully!\n");
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Vehicle not found!\n");
    }
}

int main() {
    Vehicle vehicles[MAX_VEHICLES];
    int count = load_data(vehicles);
    int choice = 0;
    while (choice != 5) {
        printf("\n***** PARKING MANAGEMENT SYSTEM *****\n");
        printf("1. Park Vehicle\n");
        printf("2. Display Parked Vehicles\n");
        printf("3. Search Vehicle\n");
        printf("4. Unpark Vehicle\n");
        printf("5. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                park_vehicle(vehicles, &count);
                break;
            case 2:
                display_vehicles(vehicles, count);
                break;
            case 3:
                search_vehicle(vehicles, count);
                break;
            case 4:
                unpark_vehicle(vehicles, &count);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}