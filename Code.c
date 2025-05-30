#include <stdio.h>
#include <string.h>
#define MAX_TRANSACTIONS 5
#define USERS 3

int main() {
    int userID[USERS] = {101, 102, 103};
    char userPassword[USERS][20] = {"1234", "5678", "9999"};
    int userAccountType[USERS] = {1, 2, 2};
    int userBalance[USERS] = {10000, 8000, 12000};
    char userName[USERS][50] = {"Ajinkya N", "Nikhil khandare", "Rameshwar kele"};
    char userMobile[USERS][15] = {"*********328", "*********456", "*********789"};
    char userBirthdate[USERS][12] = {"12/08/2006", "15/03/1995", "22/11/1988"};
    char transactionType[USERS][MAX_TRANSACTIONS][20];
    int transactionAmount[USERS][MAX_TRANSACTIONS];
    int transactionBalance[USERS][MAX_TRANSACTIONS];
    int transactionCount[USERS] = {0};

    int langChoice;
    printf("🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟\n");
    printf("          🏦 WELCOME TO SECURE BANK ATM SYSTEM 🏦\n");
    printf("🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟\n\n");
    printf("🌐 Choose Language / भाषा निवडा:\n");
    printf("1️⃣  English\n2️⃣  मराठी\n");
    printf("🔢 Enter your choice: ");
    scanf("%d", &langChoice);

    switch (langChoice) {
        case 1: { 
            int selectedAccountType;
            printf("\n🏦 Choose Account Type:\n");
            printf("1️⃣  Current Account 💼\n2️⃣  Saving Account 💰\n");
            printf("🔢 Enter your choice (1 or 2): ");
            scanf("%d", &selectedAccountType);

            if (selectedAccountType != 1 && selectedAccountType != 2) {
                printf("❌ Invalid selection!\n");
                return 1;
            } else {
                printf("✅ %s Account selected!\n", (selectedAccountType == 1) ? "Current" : "Saving");
            }

            char continueChoice;
            do {
                int menuOption;
                printf("\n🔸🔸🔸 MAIN MENU 🔸🔸🔸\n");
                printf("1️⃣  Check Balance 🧾\n2️⃣  Withdraw Cash 💸\n");
                printf("3️⃣  Deposit Cash 💰\n4️⃣  Change Password 🔄\n");
                printf("5️⃣  Exit 🚪\n6️⃣  Mini Statement 🧾\n");
                printf("🔢 Enter your choice: ");
                scanf("%d", &menuOption);

                if (menuOption == 5) {
                    printf("🎉 Thank you for using our ATM service!\n👋 Have a great day!\n");
                    break;
                }

                printf("\n🔐 AUTHENTICATION REQUIRED\n");
                int enteredID;
                char enteredPassword[20];
                printf("🆔 Enter Login ID: ");
                scanf("%d", &enteredID);
                printf("🔑 Enter Password: ");
                scanf("%s", enteredPassword);
                printf("🔍 Verifying credentials...\n");

                int userIndex = -1;
                for (int i = 0; i < USERS; i++) {
                    if (userID[i] == enteredID && strcmp(userPassword[i], enteredPassword) == 0 && userAccountType[i] == selectedAccountType) {
                        userIndex = i;
                        break;
                    }
                }

                if (userIndex == -1) {
                    printf("🚫 ACCESS DENIED! Wrong credentials or account type mismatch.\n");
                    continue;
                }

                printf("✅ LOGIN SUCCESSFUL! 🎉\n");
                printf("🙏 Welcome, %s!\n", userName[userIndex]);
                printf("📞 Mobile: %s\n", userMobile[userIndex]);
                printf("💼 Account: %s\n", (selectedAccountType == 1) ? "Current" : "Saving");

                switch (menuOption) {
                    case 1:
                        printf("\n💼 BALANCE INQUIRY\n");
                        printf("Dear %s, Your current balance is: ₹%d\n", userName[userIndex], userBalance[userIndex]);
                        break;

                    case 2: {
                        printf("\n💸 CASH WITHDRAWAL\n");
                        printf("Hello %s, Available Balance: ₹%d\n", userName[userIndex], userBalance[userIndex]);

                        int amount;
                        int oldBalance = userBalance[userIndex];
                        printf("💸 Enter amount to withdraw: ₹");
                        scanf("%d", &amount);

                        if (amount <= 0) {
                            printf("❌ Invalid amount!\n");
                        } else if (amount > userBalance[userIndex]) {
                            printf("❌ INSUFFICIENT BALANCE! Requested: ₹%d | Available: ₹%d\n", amount, userBalance[userIndex]);
                        } else {
                            userBalance[userIndex] -= amount;
                            printf("💳 Processing... ✅ Transaction Successful!\n");
                            printf("💸 Please collect your cash: ₹%d\n", amount);
                            printf("💰 Remaining Balance: ₹%d\n", userBalance[userIndex]);

                            int idx = transactionCount[userIndex] % MAX_TRANSACTIONS;
                            strcpy(transactionType[userIndex][idx], "Withdrawal");
                            transactionAmount[userIndex][idx] = amount;
                            transactionBalance[userIndex][idx] = userBalance[userIndex];
                            transactionCount[userIndex]++;

                            char wantReceipt;
                            printf("🧾 Want receipt? (y/n): ");
                            scanf(" %c", &wantReceipt);
                            if (wantReceipt == 'y' || wantReceipt == 'Y') {
                                printf("\n===============================\n");
                                printf("        🧾 RECEIPT 🧾\n");
                                printf("===============================\n");
                                printf("NAME: %s\nAccount: ***** %d\nMOBILE: %s\n", userName[userIndex], userID[userIndex], userMobile[userIndex]);
                                printf("TRANSACTION: WITHDRAWAL\n");
                                printf("-------------------------------\n");
                                printf("Initial: ₹%d\nWithdrawal: ₹%d\nBalance: ₹%d\n", oldBalance, amount, userBalance[userIndex]);
                                printf("===============================\n");
                            }
                        }
                        break;
                    }

                    case 3: {
                        printf("\n💰 CASH DEPOSIT\n");
                        printf("Hello %s, Current Balance: ₹%d\n", userName[userIndex], userBalance[userIndex]);

                        int amount;
                        int oldBalance = userBalance[userIndex];
                        printf("💰 Enter amount to deposit: ₹");
                        scanf("%d", &amount);

                        if (amount <= 0) {
                            printf("❌ Invalid amount!\n");
                        } else {
                            userBalance[userIndex] += amount;
                            printf("💳 Processing... ✅ Amount deposited successfully!\n");
                            printf("💰 New Balance: ₹%d\n", userBalance[userIndex]);

                            int idx = transactionCount[userIndex] % MAX_TRANSACTIONS;
                            strcpy(transactionType[userIndex][idx], "Deposit");
                            transactionAmount[userIndex][idx] = amount;
                            transactionBalance[userIndex][idx] = userBalance[userIndex];
                            transactionCount[userIndex]++;

                            char wantReceipt;
                            printf("🧾 Want receipt? (y/n): ");
                            scanf(" %c", &wantReceipt);
                            if (wantReceipt == 'y' || wantReceipt == 'Y') {
                                printf("\n===============================\n");
                                printf("        🧾 RECEIPT 🧾\n");
                                printf("===============================\n");
                                printf("NAME: %s\nAccount: ***** %d\nMOBILE: %s\n", userName[userIndex], userID[userIndex], userMobile[userIndex]);
                                printf("TRANSACTION: DEPOSIT\n");
                                printf("-------------------------------\n");
                                printf("Initial: ₹%d\nDeposit: ₹%d\nBalance: ₹%d\n", oldBalance, amount, userBalance[userIndex]);
                                printf("===============================\n");
                            }
                        }
                        break;
                    }

                    case 4: {
                        printf("\n🔄 PASSWORD CHANGE\n");
                        printf("Hello %s, verify current password first.\n", userName[userIndex]);

                        char oldPassword[20], newPassword[20];
                        printf("🔐 Enter current password: ");
                        scanf("%s", oldPassword);

                        if (strcmp(oldPassword, userPassword[userIndex]) == 0) {
                            printf("✅ Current password verified!\n");
                            printf("🔐 Enter new password: ");
                            scanf("%s", newPassword);

                            if (strlen(newPassword) <4) {
                                printf("❌ Password too short! Minimum 4 characters.\n");
                            } else {
                                strcpy(userPassword[userIndex], newPassword);
                                printf("🎉 Password changed successfully!\n");
                            }
                        } else {
                            printf("❌ INCORRECT PASSWORD! Change failed.\n");
                        }
                        break;
                    }

                    case 6: {
                        printf("\n🧾 MINI STATEMENT\n");
                        int count = transactionCount[userIndex] < MAX_TRANSACTIONS ? transactionCount[userIndex] : MAX_TRANSACTIONS;
                        if (count == 0) {
                            printf("❗ No transactions available!\n");
                        } else {
                            int start = (transactionCount[userIndex] >= MAX_TRANSACTIONS)
                                        ? (transactionCount[userIndex] % MAX_TRANSACTIONS)
                                        : 0;
                            for (int i = 0; i < count; i++) {
                                int idx = (start + i) % MAX_TRANSACTIONS;
                                printf("%d. %s | Amount: ₹%d | Balance: ₹%d\n", i + 1,
                                       transactionType[userIndex][idx],
                                       transactionAmount[userIndex][idx],
                                       transactionBalance[userIndex][idx]);
                            }
                        }
                        break;
                    }

                    default:
                        printf("❗ INVALID CHOICE! Select 1-6.\n");
                        break;
                }

                if (menuOption >= 1 && menuOption <= 6) {
                    do {
                        printf("\n🔁 Continue with more transactions? (y/n): ");
                        scanf(" %c", &continueChoice);
                        if (continueChoice != 'y' && continueChoice != 'Y' && continueChoice != 'n' && continueChoice != 'N') {
                            printf("❗ Enter 'y' for Yes or 'n' for No.\n");
                        }
                    } while (continueChoice != 'y' && continueChoice != 'Y' && continueChoice != 'n' && continueChoice != 'N');
                }

            } while (continueChoice == 'y' || continueChoice == 'Y');

            printf("\n🌟 Session ended! Thank you for using Secure Bank ATM! 🌟\n");
            break;
        }

        case 2:
            printf("⚠️ Marathi mini-statement part not yet added. Want me to include that as well?\n");
            break;

        default:
            printf("❗ Invalid language choice / चुकीचा भाषा पर्याय\n");
            break;
    }

    return 0;
}
