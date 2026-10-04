import os
import sys
import subprocess
import time

TEST_DIR = 'tests'
COMPILER_EXE = os.path.join('bin', 'c_compiler.exe')

# Expected exit codes for tests
EXPECTED_EXIT_CODES = {
    'test01_return42.c': 42,
    'test02_vars.c': 50,
    'test03_recursion.c': 120,
    'test04_loops.c': 0,
    'test05_switch.c': 0,
    'test06_pointers.c': 0,
    'test07_arrays.c': 0,
    'test08_globals.c': 0,
    'test09_structs.c': 0,
    'test10_strings_printf.c': 0,
    'test11_bitwise_ternary.c': 0,
    'test12_sorting.c': 0,
    'test13_fibonacci.c': 0,
    'test_if.c': 1,
    'test_if1.c': 1,
    'test_if2.c': 1,
}

def run_test(c_file):
    base_name = os.path.splitext(os.path.basename(c_file))[0]
    asm_file = os.path.join(TEST_DIR, f"{base_name}.asm")
    obj_file = os.path.join(TEST_DIR, f"{base_name}.obj")
    exe_file = os.path.join(TEST_DIR, f"{base_name}.exe")
    expected_code = EXPECTED_EXIT_CODES.get(os.path.basename(c_file), 0)

    # 1. Compile C source with c_compiler.exe
    comp = subprocess.run([COMPILER_EXE, c_file, asm_file], capture_output=True, text=True)
    if comp.returncode != 0:
        return False, f"COMPILATION ERROR:\n{comp.stderr or comp.stdout}"

    # Copy out.asm to asm_file if needed
    if os.path.exists('out.asm'):
        try:
            with open('out.asm', 'r', encoding='utf-8') as f:
                content = f.read()
            with open(asm_file, 'w', encoding='utf-8') as f:
                f.write(content)
        except Exception:
            pass

    # 2. Assemble to object file
    asm_res = subprocess.run(['nasm', '-f', 'win64', asm_file, '-o', obj_file], capture_output=True, text=True)
    if asm_res.returncode != 0:
        return False, f"Assembly error:\n{asm_res.stderr or asm_res.stdout}"

    # 3. Link with GCC
    gcc = subprocess.run(['gcc', obj_file, '-o', exe_file], capture_output=True, text=True)
    if gcc.returncode != 0:
        return False, f"GCC LINK ERROR:\n{gcc.stderr or gcc.stdout}"

    # 4. Execute program
    try:
        run = subprocess.run([exe_file], capture_output=True, text=True, timeout=5)
        actual_code = run.returncode
        if actual_code != expected_code:
            return False, f"Exit code mismatch: got {actual_code}, expected {expected_code}"
        return True, f"OK (exit code {actual_code})"
    except subprocess.TimeoutExpired:
        return False, "TIMEOUT (infinite loop or hang)"
    except Exception as e:
        return False, f"EXECUTION ERROR: {e}"

def main():
    print("=" * 70)
    print("  PURE x86-64 ASSEMBLY C COMPILER - AUTOMATED TEST SUITE")
    print("=" * 70)

    test_files = sorted([
        os.path.join(TEST_DIR, f) for f in os.listdir(TEST_DIR)
        if f.endswith('.c') and not f.startswith('temp_')
    ])

    passed = 0
    failed = 0
    results = []

    start_time = time.time()
    for t in test_files:
        test_name = os.path.basename(t)
        ok, msg = run_test(t)
        if ok:
            passed += 1
            status = "[PASS]"
        else:
            failed += 1
            status = "[FAIL]"
        results.append((test_name, status, msg))
        print(f" {status} {test_name:<28} -> {msg}")

    elapsed = time.time() - start_time

    print("=" * 70)
    print(f"  SUMMARY: {passed} PASSED, {failed} FAILED across {len(test_files)} tests in {elapsed:.2f}s")
    print("=" * 70)

    if failed > 0:
        sys.exit(1)

if __name__ == '__main__':
    main()
