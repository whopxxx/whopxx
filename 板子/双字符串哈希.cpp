namespace utils {

static int D = 127;
static int mod1 = 1e9 + 7, mod2 = 1e9 + 9;
vector<long long> pow1, pow2;
void init(int l) {
  pow1.resize(l + 1, 0);
  pow1[0] = 1; pow2 = pow1;
  for (int i = 1; i <= l; i ++)
    pow1[i] = pow1[i - 1] * D % mod1,
    pow2[i] = pow2[i - 1] * D % mod2;
}
int qmod(int v, int m) {
  return v + ((v >> 31) & m);
}
struct Hash {
  vector<long long> val1, val2;
  Hash(string s) {
    val1.reserve(s.size());
    val2.reserve(s.size());
    long long v1 = 0, v2 = 0;
    for (auto c: s) {
      v1 = (v1 * D + c) % mod1;
      v2 = (v2 * D + c) % mod2;
      val1.push_back(v1);
      val2.push_back(v2);
    }
  }
  pair<int, int> val() {
    return {val1.back(), val2.back()};
  }
  pair<int, int> val(int l, int r) {
    if (l == 0)
      return {val1[r], val2[r]};
    return {
      qmod(val1[r] - val1[l - 1] * pow1[r - l + 1] % mod1, mod1),
      qmod(val2[r] - val2[l - 1] * pow2[r - l + 1] % mod2, mod2)
    };
  }
};

}

using utils::Hash;
using utils::init;
pair<int, int> H(string s) {
  return Hash(s).val();
}

class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        init(1e5);
        map<pair<int, int>, int> mp;
        long long ans = 0;
        for (int i = 0; i < (int)words.size(); i ++) {
            auto h = Hash(words[i]);
            for (int l = 1; l <= (int)words[i].size(); l ++) {
                if (h.val(0, l - 1) == h.val(words[i].size() - l, words[i].size() - 1))
                    ans += mp[h.val(0, l - 1)];
            }
            ++ mp[h.val()];
        }
        return ans;
    }
};