# Password Manager

Simples gerenciador de senhas com cifra de césar e exportação em binários. 

## 🕹️Funcionalidades

- Menu interativo
- Senha Cifrada
- Reversão de Senha
- Exportação em binário
- Implementação da cifra de césar
## 🚨Observação
Essa cifra **não é segura** pois é simples de reverter, basta subtrair a **Key** que retornará a senha original 😯
Use apenas para fins didáticos ou aprendizados.
## Compilação
```bash 
gcc main.c menu.c utils.c credentials.c crypto.c -o nome_arquivo.exe
```
```bash 
.\nome_arquivo.exe
```