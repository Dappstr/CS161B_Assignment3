#include <iostream>
#include <iomanip>

class MembershipInfo 
{
private:
    struct Info
    {
        char planChoice{};
        int membershipMonths{};
        int personalSessions{};

        double membershipFees{};
        double personalTrainingFees{};
        double totalMembershipCosts{};
    };

public:

	Info& infoObj;

    static void welcomeMessage();
    static char readOption(char&);
    static void userInput(Info&);
    static void calcCost(Info&);

};


int main()
{
	const std::unique_ptr<MembershipInfo> p_memberStuff = std::make_unique<MembershipInfo>();

    char menuInput{};

    while (true)
    {
        p_memberStuff->welcomeMessage();

        while (menuInput != 'q' && menuInput != 'Q')
        {
            std::cout << "(Menu)>> ";

            p_memberStuff->readOption(menuInput);

            switch (menuInput)
            {
            case 'c':
            case 'C':

                p_memberStuff->userInput(p_memberStuff->infoObj);
                p_memberStuff->calcCost(p_memberStuff->infoObj);
                break;

            case 'q':
            case 'Q':
                std::cout << "Thank you for checking out my fitClub center!! Come back and be fit!\n";
                break;

            default:
                std::cout << "Input not recognized!\n";
                break;
            }

        }
    }
}

void MembershipInfo::welcomeMessage()
{
    std::cout << "Welcome to my fitClub program!!\n"
        "The cost to become a member of the fitClub center is as follows:\n\n"
        "\tThe membership fee per month for Sports Club is $20.00\n"
        "\tThe membership fee per month for Ultra Sports Club is $30.00\n"
        "\tIf the membership is bought and paid for 12 or more months, the discount is 10% off membership cost\n"
        "\tPersonal training sessions are $10.00 per session\n"
        "\tIf more than five personal training sessions are bought and paid for, the discount on each session is 20%\n\n"
        "Please pick one of the following options:\n\n"
        "\t(C/c) Calculate membership costs.\n"
        "\t(Q/q) quit this program.\n\n";
}

char MembershipInfo::readOption(char& option)
{
    std::cin >> option;
    return option;
}

void MembershipInfo::userInput(Info& input)
{
    bool contLoop = true;

    while (contLoop)
    {
        std::cout << "Would you prefer (S)ports or (U)ltra Sports Club: ";
        std::cin >> input.planChoice;

        switch (input.planChoice)
        {
        case 'S':
        case 's':
        case 'U':
        case 'u':
            contLoop = false;
            break;

        default:
            std::cout << "Invalid membership type! Please try again!\n";
            break;
        }
    }

    {
    retryMembershipAmount:

        std::cout << "How many months of membership would you like? ";
        std::cin >> input.membershipMonths;

        if (input.membershipMonths < 0)
        {
            std::cout << "Invalid number!\n";
            goto retryMembershipAmount;
        }
    }

    {
    retryPersonalSessions:

        std::cout << "How many personal training sessions would you like? ";
        std::cin >> input.personalSessions;

        if (input.personalSessions < 0)
        {
            std::cout << "Invalid number!\n";
            goto retryPersonalSessions;
        }
    }
}

void MembershipInfo::calcCost(Info& infoObj)
{
    fixed(std::cout);
    std::cout.precision(2);

    {
        if (infoObj.planChoice == 's' || infoObj.planChoice == 'S')
        {
            infoObj.membershipFees = 20 * infoObj.membershipMonths;
        }

        else if (infoObj.planChoice == 'u' || infoObj.planChoice == 'U')
        {
            infoObj.membershipFees = 30 * infoObj.membershipMonths;
        }

    }

    if (infoObj.membershipMonths >= 12)
    {
        infoObj.membershipFees = infoObj.membershipFees - (infoObj.membershipFees * 0.10);
    }

    infoObj.personalTrainingFees = 10 * infoObj.personalSessions;

    infoObj.totalMembershipCosts = infoObj.membershipFees + infoObj.personalTrainingFees;

    std::cout << '\n' << infoObj.totalMembershipCosts;
    {
        if (infoObj.membershipMonths >= 12)
        {
            std::cout << "Your membership cost after the 10% off is $" << infoObj.membershipFees;
        }

        else
        {
            std::cout << "Your membership cost is $" << infoObj.membershipFees;
        }
    }

    std::cout << "\nYour personal training cost is: $" << infoObj.personalTrainingFees;
    std::cout << "\nYour total costs is: $" << infoObj.totalMembershipCosts << '\n';
}

/*
#include <iostream>
#include <iomanip>

struct Info
{
    char planChoice             {};
    int membershipMonths        {};
	int personalSessions        {};

    double membershipFees       {};
    double personalTrainingFees {};
    double totalMembershipCosts {};
};

void welcomeMessage();

template <typename T>
T readOption(T&);

void userInput(Info&);

void calcCost(Info&);

int main()
{
	Info membersStuff {};
    char menuInput{};

    while (true)
    {
        welcomeMessage();

        while (menuInput != 'q' && menuInput != 'Q')
        {
            std::cout << "(Menu)>> ";

            readOption<char>(menuInput);

            switch (menuInput)
            {
            case 'c':
            case 'C':

            	userInput(membersStuff);
                calcCost(membersStuff);
                break;

            case 'q':
            case 'Q':
                std::cout << "Thank you for checking out my fitClub center!! Come back and be fit!\n";
                break;

            default:
                std::cout << "Input not recognized!\n";
                break;
            }

        }
    }
}

void welcomeMessage()
{
    std::cout << "Welcome to my fitClub program!!\n"
        "The cost to become a member of the fitClub center is as follows:\n\n"
        "\tThe membership fee per month for Sports Club is $20.00\n"
        "\tThe membership fee per month for Ultra Sports Club is $30.00\n"
        "\tIf the membership is bought and paid for 12 or more months, the discount is 10% off membership cost\n"
        "\tPersonal training sessions are $10.00 per session\n"
        "\tIf more than five personal training sessions are bought and paid for, the discount on each session is 20%\n\n"
        "Please pick one of the following options:\n\n"
        "\t(C/c) Calculate membership costs.\n"
        "\t(Q/q) quit this program.\n\n";
}

template <typename T>
T readOption(T& option)
{
    std::cin >> option;
    return option;
}

void userInput(Info& input)
{
    bool contLoop = true;

    while (contLoop)
    {
        std::cout << "Would you prefer (S)ports or (U)ltra Sports Club: ";
        std::cin >> input.planChoice;

        switch (input.planChoice)
        {
	        case 'S':
	        case 's':
	        case 'U':
	        case 'u':
	            contLoop = false;
	            break;

	        default:
	            std::cout << "Invalid membership type! Please try again!\n";
	            break;
        }
    }

    {
    retryMembershipAmount:

        std::cout << "How many months of membership would you like? ";
        std::cin >> input.membershipMonths;

        if (input.membershipMonths < 0)
        {
            std::cout << "Invalid number!\n";
            goto retryMembershipAmount;
        }
    }

    {
    retryPersonalSessions:

    	std::cout << "How many personal training sessions would you like? ";
        std::cin >> input.personalSessions;

        if (input.personalSessions < 0)
        {
            std::cout << "Invalid number!\n";
            goto retryPersonalSessions;
        }
    }
}

void calcCost(Info& infoObj)
{
    fixed(std::cout);
    std::cout.precision(2);
    
    {
	    if (infoObj.planChoice == 's' || infoObj.planChoice == 'S')
	    {
	        infoObj.membershipFees = 20 * infoObj.membershipMonths;
	    }

	    else if (infoObj.planChoice == 'u' || infoObj.planChoice == 'U')
	    {
	        infoObj.membershipFees = 30 * infoObj.membershipMonths;
	    }

	}

    if (infoObj.membershipMonths >= 12)
    {
        infoObj.membershipFees = infoObj.membershipFees - ( infoObj.membershipFees * 0.10);
    }

    infoObj.personalTrainingFees = 10 * infoObj.personalSessions;

    infoObj.totalMembershipCosts = infoObj.membershipFees + infoObj.personalTrainingFees;

    std::cout << '\n' << infoObj.totalMembershipCosts;
    {
        if (infoObj.membershipMonths >= 12)
        {
            std::cout << "Your membership cost after the 10% off is $" << infoObj.membershipFees;
        }

        else
        {
            std::cout << "Your membership cost is $" << infoObj.membershipFees;
        }
    }

    std::cout << "\nYour personal training cost is: $" << infoObj.personalTrainingFees;
    std::cout << "\nYour total costs is: $" << infoObj.totalMembershipCosts << '\n';
}
*/