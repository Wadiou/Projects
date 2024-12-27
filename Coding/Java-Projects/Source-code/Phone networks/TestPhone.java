package S1.MiniProject;

import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

class SimCard {
    private final String number;
    public static int[] Networks_number = new int[]{5, 6, 7};
    public static String[] Networks = new String[]{"Ooredoo", "Mobilis", "Djezzi"};

    private double credit = 0;

    public SimCard(final String number) {
        this.number = number;
    }

    public SimCard(final String number, int credit) {
        this.number = number;
        this.credit = credit;
    }

    public void addCredit(int credit) {
        this.credit += credit;
    }

    public void deductCredit(int credit) {
        if (sufficient(credit)) {
            this.credit -= credit;
        } else {
            System.out.println("Insufficient credit to make this call.");
        }
    }

    public boolean sufficient(int credit) {
        return this.credit >= credit;
    }

    public String getNumber() {
        return number;
    }

    public double getCredit() {
        return credit;
    }

    public static int extractNetworkDigits(String phoneNumber) {
        return Integer.parseInt(phoneNumber.charAt(1) + "");
    }

    // Find the index of the network
    public static int getNetworkIndex(int networkDigit) {
        for (int i = 0; i < Networks_number.length; i++) {
            if (Networks_number[i] == networkDigit) {
                return i;
            }
        }
        return -1;
    }

    @Override
    public String toString() {
        int networkDigit = extractNetworkDigits(number);
        int index = getNetworkIndex(networkDigit);
        String networkName = (index != -1) ? Networks[index] : "Unknown";
        return String.format("Network: %s, Number: %s, Credit: %.2f", networkName, number, credit);
    }
}


class Location {
    private double xCoordinate, yCoordinate;

    public Location(double xCoordinate, double yCoordinate) {
        this.xCoordinate = xCoordinate;
        this.yCoordinate = yCoordinate;
    }

    public void updateLocation(double xCoordinate, double yCoordinate) {
        this.xCoordinate = xCoordinate;
        this.yCoordinate = yCoordinate;
    }

    public double distanceTo(Location other) {
        return Math.sqrt(Math.pow(this.xCoordinate-other.xCoordinate,2) + Math.pow(this.yCoordinate-other.yCoordinate,2));
    }
    @Override
    public String toString() {
        return String.format("(%.2f, %.2f)", xCoordinate, yCoordinate);
    }
}

class Antenna {
    private static final int CAPACITY = 10;
    private final Location location;
    private final double coverageRadius;
    private int activeCalls = 0;

    public Antenna(Location location, double coverageRadius) {
        this.location = location;
        this.coverageRadius = coverageRadius;
    }

    public boolean canAcceptNewCall() {
        return activeCalls < CAPACITY;
    }

    public void incrementActiveCalls() {
        if (canAcceptNewCall()) {
            activeCalls++;
        }
    }

    public void decrementActiveCalls() {
        if (activeCalls > 0) {
            activeCalls--;
        }
    }

    public boolean isPhoneInCoverage(Location phoneLocation) {
        return location.distanceTo(phoneLocation) <= coverageRadius; // Compare distance with antenna radius
    }

    public Location getLocation() {
        return location;
    }
}

class Network {
    private final ArrayList<Antenna> antennas = new ArrayList<>();
    private int ID;

    public Network(String network) {
        switch (network) {
            case "Ooredoo":
                ID = SimCard.Networks_number[0];
                break;
            case "Mobilis":
                ID = SimCard.Networks_number[1];
                break;
            case "Djezzi":
                ID = SimCard.Networks_number[2];
                break;
            default:
                break;
        }
    }

    public void addAntenna(Antenna antenna) {
        antennas.add(antenna);
    }

    public Antenna findNearestAntenna(Location location) {
        Antenna nearest = null;
        double minDistance = Double.MAX_VALUE;

        for (Antenna antenna : antennas) {
            if (antenna.isPhoneInCoverage(location) && antenna.canAcceptNewCall()) {
                double distance = location.distanceTo(antenna.getLocation());
                if (distance < minDistance) {
                    nearest = antenna;
                    minDistance = distance;
                }
            }
        }

        return nearest;
    }

    public int getID() {
        return ID;
    }
}

class Phone {
    private int battery;
    private SimCard simCard;
    private Location location;
    private boolean onCall;
    private int UID ;
    private static int UID_counter = 0 ;

    public Phone(int battery, SimCard simCard, Location location) {
        this.battery = battery;
        this.simCard = simCard;
        this.location = location;
        this.UID = UID_counter++;
        this.onCall = false;

    }

    public boolean canMakeCall(int requiredCredit) {
        return battery > 0 && simCard != null && simCard.sufficient(requiredCredit);
    }

    public void makeCall(Network network, int callDuration) {
        int requiredCredit = callDuration ;
        if (SimCard.extractNetworkDigits(this.simCard.getNumber()) != network.getID())
        {
            requiredCredit*=3;
        }
        if (!canMakeCall(requiredCredit)) {
            System.out.println("Cannot make the call.");
            return;
        }

        Antenna nearest = network.findNearestAntenna(location);
        if (nearest == null) {
            System.out.println("No available antenna in range.");
            return;
        }

        System.out.println("Call connected!");
        nearest.incrementActiveCalls();
        simCard.deductCredit(requiredCredit);
        battery-=(int) callDuration / 100;
        this.onCall = true;
        for (int i = 0; i < 100000*callDuration; i++) {}
        endCall(nearest);

    }

    public void endCall(Antenna antenna) {
        if (onCall) {
            System.out.println("Call ended.");
            antenna.decrementActiveCalls();
            this.onCall = false;
        }
    }

    public void movePhone(double newX, double newY, Network network) {
        location.updateLocation(newX, newY);

        if (onCall) {
            Antenna currentAntenna = network.findNearestAntenna(location);
            if (currentAntenna == null) {
                System.out.println("Call disconnected due to moving out of coverage.");
                this.onCall = false;
            }
        }
    }
    @Override
    public String toString(){
        return "UID : " + this.UID + ", SimCard : " + this.simCard.toString() + ", Battery : " + this.battery + ", Location : " + this.location.toString() + ", Oncall : " + (this.onCall == true ? "Yes" : "No") + " .\n" ;
    }
}


public class TestPhone {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Random random = new Random();
        System.out.print("Enter the number of phones to create: ");
        int numPhones = scanner.nextInt();
        System.out.print("Enter the number of antennas to create: ");
        int numAntennas = scanner.nextInt();
        ArrayList<Phone> phones = new ArrayList<>();
        ArrayList<Antenna> antennas = new ArrayList<>();

        for (int i = 0; i < numPhones; i++) {
            String networkDigits = SimCard.Networks_number[random.nextInt(SimCard.Networks_number.length)] + ""; // Random Network (0-2)
            String randomPhoneNumber = "0" + networkDigits + (10000000 + random.nextInt(90000000)); // Random 7-digit number
            SimCard simCard = new SimCard(randomPhoneNumber, random.nextInt(100)); // Random credit (0-99)
            Location phoneLocation = new Location(random.nextDouble() * 200 - 100, random.nextDouble() * 200 - 100); // Random location ([-100,100],[-100,100])
            Phone newPhone = new Phone(100, simCard, phoneLocation) ;
            phones.add(newPhone); // Adding the new Phone
            System.out.println("Created Phone " + (i + 1) + newPhone);
        }

        // Generate antennas with random locations and coverage radius
        for (int i = 0; i < numAntennas; i++) {
            Location antennaLocation = new Location(random.nextDouble() * 200 - 100, random.nextDouble() * 200 - 100); // Random location ([-100,100],[-100,100])
            double coverageRadius = 20 + random.nextDouble() * 50; // Coverage radius (20-70)
            antennas.add(new Antenna(antennaLocation, coverageRadius));
            System.out.println("Created Antenna " + (i + 1) + " at location: " + antennaLocation + " with radius: " + coverageRadius);
        }

        // Create networks and add antennas
        Network network1 = new Network("Ooredoo");
        Network network2 = new Network("Mobilis");
        Network network3 = new Network("Djezzi");
        for (Antenna antenna : antennas) {
            int randomNetwork = random.nextInt(3);
            switch (randomNetwork) {
                case 0 -> network1.addAntenna(antenna);
                case 1 -> network2.addAntenna(antenna);
                case 2 -> network3.addAntenna(antenna);
            }
        }

        // Randomly select a network and call duration for each phone
        for (Phone phone : phones) {
            int randomNetwork = random.nextInt(3);
            Network selectedNetwork = switch (randomNetwork) {
                case 0 -> network1;
                case 1 -> network2;
                case 2 -> network3;
                default -> null;
            };
            int randomCallDuration = 5 + random.nextInt(15); // Call duration between 5 and 20 seconds
            System.out.println("\nAttempting a call for phone: " + phone + "On network: " + SimCard.Networks[randomNetwork]);
            phone.makeCall(selectedNetwork, randomCallDuration);
        }
        scanner.close();
    }
}