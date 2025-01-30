import os
import subprocess

def get_files_by_extension(directory=".", extensions=None):
    """
    Busca arquivos com extensões especificadas no diretório.
    
    :param directory: Diretório para buscar os arquivos (padrão é o diretório atual).
    :param extensions: Lista de extensões a serem buscadas (e.g., [".cpp", ".h"])
    :return: Dicionário com extensões como chaves e listas de arquivos como valores.
    """
    if extensions is None:
        extensions = [".cpp", ".h"]

    files = {ext: [] for ext in extensions}
    for f in os.listdir(directory):
        for ext in extensions:
            if f.endswith(ext):
                files[ext].append(f)
    return files

def compile_with_gpp(source_files, output_name, flags=None):
    """
    Compila arquivos fonte usando G++.
    
    :param source_files: Lista de arquivos fonte (e.g., ["main.cpp", "utils.cpp"])
    :param output_name: Nome do arquivo de saída (e.g., "program")
    :param flags: Lista de flags do G++ (e.g., ["-Wall", "-O2"])
    """
    if not source_files:
        print("Nenhum arquivo fonte encontrado para compilar.")
        return
    
    if flags is None:
        flags = []

    # Comando G++
    command = ["g++"] + source_files + flags + ["-o", output_name]

    # Exibe o comando para depuração
    print("Comando G++:", " ".join(command))

    # Executa o comando
    try:
        subprocess.run(command, check=True)
        print(f"Compilação bem-sucedida: {output_name}")
    except subprocess.CalledProcessError as e:
        print("Erro durante a compilação:", e)

def main():
    print("Bem-vindo ao Automatizador G++!")
    
    # Obtém arquivos no diretório atual
    extensions = [".cpp", ".h"]
    files = get_files_by_extension(extensions=extensions)
    
    # Exibe os arquivos encontrados
    for ext, file_list in files.items():
        if file_list:
            print(f"Arquivos {ext}: {', '.join(file_list)}")
    
    # Verifica se há arquivos para compilar
    source_files = files[".cpp"]
    if not source_files:
        print("Nenhum arquivo .cpp encontrado para compilar.")
        return
    
    # Solicita o nome do arquivo de saída
    output_name = input("Digite o nome do arquivo executável (pressione Enter para usar 'default'): ").strip()
    if not output_name:
        output_name = "default"  # Nome padrão

    # Solicita flags opcionais
    flags = input("Digite as flags opcionais do G++ separadas por espaço (ou deixe em branco): ").split()

    # Compila os arquivos
    compile_with_gpp(source_files, output_name, flags)

if __name__ == "__main__":
    main()
