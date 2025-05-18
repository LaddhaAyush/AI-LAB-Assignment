import java.util.*;

public class CryptArithmeticSolver {

    // Function to check if the equation SEND + MORE = MONEY is satisfied
    static boolean isValid(int S, int E, int N, int D, int M, int O, int R, int Y) {
        int send = 1000 * S + 100 * E + 10 * N + D;
        int more = 1000 * M + 100 * O + 10 * R + E;
        int money = 10000 * M + 1000 * O + 100 * N + 10 * E + Y;
        return send + more == money;
    }

    public static void main(String[] args) {
        // Try all digit combinations for S, E, N, D, M, O, R, Y
        for (int S = 1; S <= 9; S++)       // S ≠ 0
        for (int E = 0; E <= 9; E++)
        for (int N = 0; N <= 9; N++)
        for (int D = 0; D <= 9; D++)
        for (int M = 1; M <= 9; M++)       // M ≠ 0
        for (int O = 0; O <= 9; O++)
        for (int R = 0; R <= 9; R++)
        for (int Y = 0; Y <= 9; Y++) {

            // Check if all digits are unique
            Set<Integer> digits = new HashSet<>(Arrays.asList(S, E, N, D, M, O, R, Y));
            if (digits.size() == 8) {
                // If equation is valid, print the solution
                if (isValid(S, E, N, D, M, O, R, Y)) {
                    System.out.println("Solution found:");
                    System.out.println("S = " + S);
                    System.out.println("E = " + E);
                    System.out.println("N = " + N);
                    System.out.println("D = " + D);
                    System.out.println("M = " + M);
                    System.out.println("O = " + O);
                    System.out.println("R = " + R);
                    System.out.println("Y = " + Y);
                    return;
                }
            }
        }

        // If no solution is found
        System.out.println("No solution found.");
    }
}
