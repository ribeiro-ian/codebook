// O(n + m)
// lps[i] = comprimento do maior prefixo próprio de p[0..i] que também é sufixo
// Prefixo próprio é um prefixo que não é a string inteira
// Usos:
//   - Busca de padrão único (igual Z, mas mais natural para busca online)
//   - Busca online/streaming: processa t caractere a caractere sem ter t completo
//   - Menor período de string: n - lps[n-1] é o período mínimo
//   - Autômato de string: transformar lps em DFA para múltiplas consultas no mesmo padrão

// Computa o array lps
void computeLPS(string pattern, int m, vector<int> &lps){
    int length = 0;
    lps[0] = 0; // lps[0] é sempre 0
    int i = 1;
    while (i < m){
        if (pattern[i] == pattern[length]){
            length++;
            lps[i] = length;
            i++;
        }
        else {
            if (length != 0){
                length = lps[length - 1]; // tenta prefixo menor
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP: busca pattern em text, retorna índices (0-based) de cada ocorrência
vector<int> kmp(string pattern, string text){
    int m = pattern.length();
    int n = text.length();
    vector<int> ans;
    vector<int> lps(m);

    computeLPS(pattern, m, lps);
    int i = 0; // índice no texto
    int j = 0; // índice no padrão
    while (i < n){
        if (pattern[j] == text[i]){
            i++;
            j++;
        }
        if (j == m){
            // padrão encontrado — salva posição inicial
            ans.push_back(i - j);
            j = lps[j - 1]; // continua buscando overlaps
        }
        else if (i < n && pattern[j] != text[i]){
            if (j != 0){
                j = lps[j - 1]; // recua sem mover i
            }
            else {
                i++;
            }
        }
    }
    return ans;
}