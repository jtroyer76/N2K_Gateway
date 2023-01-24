Import('env')

env.Replace(SRC_FILTER=["+<*>", "-<hal*>"])

if "ARDUINO_M5STACK_Core2" in env.get("CPPDEFINES", []):
    #env.Append(CPPPATH=[realpath("hal/M5Core2")])
    env.Append(SRC_FILTER=["+<hal/M5Core2>"])

