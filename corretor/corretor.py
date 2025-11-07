# -*- coding: utf-8 -*-

import glob
import os
import re
import subprocess
import time  # <--- MODIFICADO (Importa o módulo de tempo)

class Corrector(object):
    def __init__(self, max_time: int = 5) -> None:
        self.__max_time = max_time
    
    def __list_test_files(self):
        files = glob.glob(f'./tests/*.txt')
        files.sort()
        return files
    
    def __compile(self):
        out = subprocess.Popen(['make', 'clean'], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out.communicate()
        
        out = subprocess.Popen(['make'], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        stdout, stderr = out.communicate()
        stdout = stdout.decode('utf8').strip()
        stderr = '' if stderr is None else stderr.decode('utf8').strip()

        if re.search(r'\d+ errors? generated\.', stdout):
            return 'error'

        if 'error:' in stdout.lower():
            print(stdout)
            return 'error'

        if stdout or stderr:
            print(stdout)
            return 'warning'
        return 'ok'

    def __compare_outputs(self, file1, file2):
        data_file1 = open(file1, 'r', encoding='utf-8').read().replace(' ', '').replace('\n', '')
        data_file2 = open(file2, 'r', encoding='utf-8').read().replace(' ', '').replace('\n', '')
        if data_file1 == data_file2:
            return True
        return False
    
    def __run_test(self, test_case):
        # <--- MODIFICADO (Registra o tempo de início)
        start_time = time.perf_counter() 
        
        p = subprocess.Popen(f'./exe < {test_case} > output.out', shell=True)
        try:
            p.wait(self.__max_time)
            
            # <--- MODIFICADO (Registra o tempo de fim e calcula a duração)
            end_time = time.perf_counter()
            duration = end_time - start_time
            
            # <--- MODIFICADO (Retorna status 'success' e a duração)
            return 'success', duration 
        
        except subprocess.TimeoutExpired:
            p.kill()
            # <--- MODIFICADO (Retorna status 'timeout' e None para duração)
            return 'timeout', None 
        # (A linha 'return True' foi removida e substituída acima)

    def __check_response(self, input_test_cases):
        correct = 0
        for input_test_case in input_test_cases:
            print(f'     {os.path.basename(input_test_case)}', end=' ')
            
            # <--- MODIFICADO (Recebe status e duração do __run_test)
            status, duration = self.__run_test(input_test_case)
            
            # <--- MODIFICADO (Verifica o status de timeout)
            if status == 'timeout':
                print('\x1b[6;30;41m EXCEDEU O TEMPO \x1b[0m')
                continue
            
            # <--- MODIFICADO (Se chegou aqui, status é 'success' e temos a duração)
            if self.__compare_outputs('output.out', input_test_case.replace('.txt', '.out')):
                # <--- MODIFICADO (Exibe OK e o tempo de execução)
                print(f'\x1b[6;30;42m OK \x1b[0m (em {duration:.4f}s)')
                correct += 1
            else:
                # <--- MODIFICADO (Exibe ER e o tempo de execução)
                print(f'\x1b[6;30;41m ER \x1b[0m (em {duration:.4f}s)')
                print(f'         Esperado: {input_test_case.replace(".txt", ".out")}')
                print(f'         Obtido: output.out')
        return 10.0 * correct / len(input_test_cases)
    
    def run(self):
        flag = False
        print(f'Analisando atividade:')

        if not os.path.exists('./Makefile'):
            print('   Arquivo "Makefile" não existe!')
            flag = True
        
        if not os.path.exists('./tests'):
            print('   A pasta de arquivos de teste não existe!')
            flag = True
        
        input_cases = self.__list_test_files()
        if len(input_cases) == 0:
            print('   É necessário pelo menos um arquivo de teste (arquivo ".txt")!')
            flag = True
        for f in input_cases:
            if not os.path.exists(f.replace('.txt', '.out')):
                flag = True
                print(f'   O arquivo de teste {os.path.basename(f)} não possui um arquivo de saída correspondente (arquivo ".out")!')
        if flag:
            return
        
        print('\nCompilando...')
        compilation_response = self.__compile()
        
        if compilation_response == 'error':
            grade = 0.0
            print('\x1b[6;30;43m   Erro de compilação!   \x1b[0m')
        else:
            factor = 1.0
            if compilation_response == 'warning':
                print('\x1b[6;30;43m   Seu código possui Warnings. A nota será reduzida pela metade!   \x1b[0m')
                factor = 0.5
            
            print('\nExecutando testes:')
            grade = self.__check_response(input_cases) * factor
        
        print(f'\n{"="*50}')
        print(f'Nota na atividade: {grade:.2f}')
        print(f'{"="*50}')
        
        if os.path.exists('output.out'):
            os.remove('output.out')


if __name__ == '__main__':
    Corrector(max_time=5).run()