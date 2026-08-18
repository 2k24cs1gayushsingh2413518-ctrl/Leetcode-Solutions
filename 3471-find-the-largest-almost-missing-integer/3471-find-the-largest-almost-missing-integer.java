import java.util.*;

class Solution {
    public int largestInteger(int[] nums, int k) {
        
        int[] count = new int[51];

        // Har size-k subarray ko check karo
        for (int i = 0; i <= nums.length - k; i++) {
            
            Set<Integer> set = new HashSet<>();

            // Current subarray ke distinct elements
            for (int j = i; j < i + k; j++) {
                set.add(nums[j]);
            }

            // Har distinct element ka subarray count badhao
            for (int num : set) {
                count[num]++;
            }
        }

        // Sabse bada number jiska count exactly 1 hai
        for (int num = 50; num >= 0; num--) {
            if (count[num] == 1) {
                return num;
            }
        }

        return -1;
    }
}