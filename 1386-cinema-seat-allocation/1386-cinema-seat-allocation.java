import java.util.*;

class Solution {
    public int maxNumberOfFamilies(int n, int[][] reservedSeats) {
        
        // Sirf wahi rows store karenge jisme reserved seats hain
        Map<Integer, Integer> map = new HashMap<>();

        // Seats 2-9 hi important hain
        for (int[] seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            if (col >= 2 && col <= 9) {
                // col seat ko bit me convert kar rahe hain
                map.put(row, map.getOrDefault(row, 0) | (1 << col));
            }
        }

        // Har completely empty row me 2 groups aa sakte hain
        int answer = (n - map.size()) * 2;

        for (int mask : map.values()) {
            
            // Seats 2,3,4,5
            boolean left = (mask & (1 << 2)) == 0 &&
                          (mask & (1 << 3)) == 0 &&
                          (mask & (1 << 4)) == 0 &&
                          (mask & (1 << 5)) == 0;

            // Seats 4,5,6,7
            boolean middle = (mask & (1 << 4)) == 0 &&
                             (mask & (1 << 5)) == 0 &&
                             (mask & (1 << 6)) == 0 &&
                             (mask & (1 << 7)) == 0;

            // Seats 6,7,8,9
            boolean right = (mask & (1 << 6)) == 0 &&
                            (mask & (1 << 7)) == 0 &&
                            (mask & (1 << 8)) == 0 &&
                            (mask & (1 << 9)) == 0;

            if (left && right) {
                // Dono side groups possible
                answer += 2;
            } else if (left || middle || right) {
                // Sirf ek group possible
                answer += 1;
            }
        }

        return answer;
    }
}