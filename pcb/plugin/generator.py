import pcbnew as kc
import os
import importlib.util
import importlib.machinery
import sys
import importlib
import subprocess
import sys


def install_package(package):
    subprocess.check_call([sys.executable, "-m", "pip", "install", package])


class Runner(kc.ActionPlugin):

    def defaults(self):
        self.plugin_dir = os.path.dirname(os.path.abspath(__file__))
        self.name = "scripting"
        self.category = "Modify PCB"
        self.description = ""
        self.show_toolbar_button = True
        self.icon_file_name = os.path.join(self.plugin_dir, 'scripting.png')

    def Run(self):
        self.RunScript()

    def RunScript(self):
        board = kc.GetBoard()
        boardfile = board.GetFileName()
        board_path = os.path.abspath(boardfile)
        board_dir = os.path.dirname(board_path)
        os.chdir(board_dir)

        script_dir = os.path.join(board_dir, "scripting")
        package_name = "scripting"

        if os.path.isdir(script_dir):
            self.Refresh(script_dir)
            loader = importlib.machinery.SourceFileLoader(
                package_name, os.path.join(script_dir, '__init__.py'))
            spec = importlib.util.spec_from_loader(package_name, loader)
            module = importlib.util.module_from_spec(spec)
            sys.modules[package_name] = module
            spec.loader.exec_module(module)

            if hasattr(module, 'main'):
                module.main()

    def Refresh(self, script_dir):
        import importlib
        import os
        import sys

        if script_dir not in sys.path:
            sys.path.append(script_dir)

        modules_to_reload = []

        for root, dirs, files in os.walk(script_dir):
            for filename in files:
                if filename.endswith(".py") and filename != os.path.basename(__file__):
                    relative_path = os.path.relpath(
                        os.path.join(root, filename), script_dir)

                    module_dir = os.path.dirname(relative_path)
                    if module_dir not in sys.path:
                        sys.path.append(module_dir)

                    module_name = os.path.splitext(relative_path)[
                        0].replace(os.path.sep, '.')

                    modules_to_reload.append(module_name)

        for module_name in sorted(modules_to_reload, key=lambda x: x.count('.'), reverse=True):
            if module_name in sys.modules:
                del sys.modules[module_name]

        for module_name in modules_to_reload:
            importlib.import_module(module_name)


Runner().register()
