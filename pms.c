#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VEHICLES 10
#define FEE_PER_HOUR 10 

struct Vehicle 
{
    char vehicleNo[20];
    int slotNo;
    time_t parkedTime; 
};

int LoadData(struct Vehicle vehicles[]) 
{
    FILE *file = fopen("parking.txt", "r");
    if (file == NULL) 
    {
        printf("Error opening file. Starting with an empty parking lot.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%s %d %ld", vehicles[count].vehicleNo, &vehicles[count].slotNo, &vehicles[count].parkedTime) != EOF) 
    {
        count++;
    }
    fclose(file);
    return count;
}

int SaveData(struct Vehicle vehicles[], int count) 
{
    FILE *file = fopen("parking.txt", "w");
    if (file == NULL) 
    {
        printf("Error opening file for saving.\n");
        return 0;
    }
    for (int i = 0; i < count; i++) 
    {
        fprintf(file, "Vehicle No. :%s , Slot No. :%d , Fee :%ld\n", vehicles[i].vehicleNo, vehicles[i].slotNo, vehicles[i].parkedTime);
    }
    fclose(file);
    return 1;
}

int AllocateSlot(struct Vehicle vehicles[], int count) 
{
    for (int i = 0; i < MAX_VEHICLES; i++) 
    {
        int slotAvailable = 1;
        for (int j = 0; j < count; j++) 
        {
            if (vehicles[j].slotNo == i) 
            {
                slotAvailable = 0;
                break;
            }
        }
        if (slotAvailable) 
        {
            return i;
        }
    }
    return -1; 
}

void ParkVehicle(struct Vehicle vehicles[], int *count) 
{
    if (*count >= MAX_VEHICLES) 
    {
        printf("**** PARKING IS FULL ****\n");
        return;
    }
    struct Vehicle newVehicle;
    printf("Enter vehicle number: ");
    scanf("%s", newVehicle.vehicleNo);

    newVehicle.slotNo = AllocateSlot(vehicles, *count);
    if (newVehicle.slotNo == -1) 
    {
        printf("No available slots!\n");
        return;
    }

    newVehicle.parkedTime = time(NULL);
    vehicles[*count] = newVehicle;
    (*count)++;
    if (SaveData(vehicles, *count)) 
    {
        printf("Vehicle parked at slot number: %d\n", newVehicle.slotNo);
    }
}

void CalculateFee(struct Vehicle vehicle) 
{
    time_t currentTime = time(NULL);
    double hoursParked = (double)(currentTime - vehicle.parkedTime) / 3600;
    double fee = hoursParked * FEE_PER_HOUR;
    printf("Vehicle No: %s, Parked for: %.2f hours, Fee: Rupees %.2f\n", vehicle.vehicleNo, hoursParked, fee);
}

void DisplayVehicles(struct Vehicle vehicles[], int count) 
{
    if (count == 0) 
    {
        printf("\nNo vehicles are parked currently.\n");
        return;
    }

    printf("\nParked Vehicles:\n");
    for (int i = 0; i < count; i++) 
    {
        printf("Slot No: %d\n", vehicles[i].slotNo);
        CalculateFee(vehicles[i]);
    }
}

void SearchVehicle(struct Vehicle vehicles[], int count) 
{
    char searchNo[20];
    printf("Enter vehicle number to search: ");
    scanf("%s", searchNo);

    int found = 0;
    for (int i = 0; i < count; i++) 
    {
        if (strcmp(vehicles[i].vehicleNo, searchNo) == 0) {
            printf("Vehicle found!\n");
            printf("Vehicle No: %s, Slot No: %d\n", vehicles[i].vehicleNo, vehicles[i].slotNo);
            CalculateFee(vehicles[i]);
            found = 1;
            break;
        }
    }
    if (!found) 
    {
        printf("Vehicle not found!\n");
    }
}

int main() 
{
    struct Vehicle vehicles[MAX_VEHICLES];
    int count = LoadData(vehicles);
    int choice = 0;
    while (choice != 4) 
    {
        printf("\n***** PARKING MANAGEMENT SYSTEM *****\n");
        printf("1. Park Vehicle\n");
        printf("2. Display Parked Vehicles\n");
        printf("3. Search Vehicle\n");
        printf("4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                ParkVehicle(vehicles, &count);
                break;
            case 2:
                DisplayVehicles(vehicles, count);
                break;
            case 3:
                SearchVehicle(vehicles, count);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}