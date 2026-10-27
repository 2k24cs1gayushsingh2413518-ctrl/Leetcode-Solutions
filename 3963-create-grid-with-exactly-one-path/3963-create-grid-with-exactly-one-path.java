import java.util.Arrays;

class Solution {
    public String[] createGrid(int m, int n) {
        char[][] grid = new char[m][n];
        
        // 1. Fill the entire grid with obstacles ('#')
        for (int i = 0; i < m; i++) {
            Arrays.fill(grid[i], '#');
        }
        
        // 2. Clear the first row to allow rightward movement
        Arrays.fill(grid[0], '.');
        
        // 3. Clear the last column to allow downward movement
        for (int i = 0; i < m; i++) {
            grid[i][n - 1] = '.';
        }
        
        // 4. Convert the char array into the required String array format
        String[] ans = new String[m];
        for (int i = 0; i < m; i++) {
            ans[i] = new String(grid[i]);
        }
        
        return ans;
    }
}