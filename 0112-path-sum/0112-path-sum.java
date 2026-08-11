class Solution {
    public boolean hasPathSum(TreeNode root, int targetSum) {

        // Tree empty hai
        if (root == null) {
            return false;
        }

        // Agar leaf node hai
        if (root.left == null && root.right == null) {
            return root.val == targetSum;
        }

        // Current node ki value subtract karo
        int remaining = targetSum - root.val;

        // Left ya Right side check karo
        return hasPathSum(root.left, remaining) ||
               hasPathSum(root.right, remaining);
    }
}