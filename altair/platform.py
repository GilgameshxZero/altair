import typing


def is_notebook_kernel_code(
    global_scope: typing.Optional[typing.Dict[str, str]] = None,
) -> bool:
    """Detect if current notebook kernel is from Code."""
    return "__vsc_ipynb_file__" in global_scope


def get_notebook_name(
    global_scope: typing.Optional[typing.Dict[str, str]] = None,
) -> str:
    """Guess the name of an `.ipynb` based on the session name of the kernel."""
    import os

    if is_notebook_kernel_code(global_scope):
        return os.path.basename(global_scope.get("__vsc_ipynb_file__"))
    session_name = os.getenv("JPY_SESSION_NAME") or global_scope.get("__session__")
    return os.path.basename(session_name)


def get_notebook_assets_path(
    global_scope: typing.Optional[typing.Dict[str, str]] = None,
) -> str:
    """Notebooks of the name `NAME.ID.ipynb` all share an assets directory of `NAME.ipynb.assets`."""
    import os

    if is_notebook_kernel_code(global_scope):
        vsc_ipynb_file = global_scope.get("__vsc_ipynb_file__")
        dirpath = os.path.dirname(vsc_ipynb_file)
        basename = os.path.basename(vsc_ipynb_file)
    else:
        dirpath = os.path.dirname(
            os.getenv("JPY_SESSION_NAME") or global_scope.get("__session__")
        )
        basename = get_notebook_name(global_scope=global_scope)
    basename_prefix = basename.rsplit(".", 2)[0]
    return os.path.join(dirpath, basename_prefix + ".ipynb.assets" + os.path.sep)


def import_global(
    global_scope: typing.Dict[str, str],
    object_name: str,
    short_name: str = "",
    context_module_name: str = "",
    value: typing.Any = None,
):
    """<https://stackoverflow.com/a/64791087>.

    Use this statement to import inside a function, but effective as import at the top of the module. Optionally, use `value` to set a global variable.
    """
    if short_name == "":
        short_name = object_name
    if value is not None:
        global_scope[short_name] = value
    elif context_module_name == "":
        global_scope[short_name] = __import__(object_name)
    else:
        context_module = __import__(context_module_name, fromlist=[object_name])
        global_scope[short_name] = getattr(context_module, object_name)

    # Additionally, also import it into this scope.
    globals()[short_name] = global_scope[short_name]

    return global_scope[short_name]


def import_globals_notebook(global_scope: typing.Dict[str, str]):
    """Import commonly used globals under standard namespaces. Should pass `globals()` as the first argument.

    Typically, call at the top of the notebook. Supports both Code notebook editors as well as the standard JupyterLab interface in the browser.
    """
    base_module = __name__.split(".", 1)[0]
    print("base_module =", base_module)
    import_global(global_scope, base_module)

    import_global(global_scope, "os")
    import_global(global_scope, "glob")
    import_global(global_scope, "pathlib")
    import_global(global_scope, "dotenv")
    import_global(global_scope, "pp", "", "pprint")
    import_global(global_scope, "json")
    import_global(global_scope, "tqdm", "", "tqdm.auto")
    import_global(global_scope, "dill")
    import_global(global_scope, "pyplot", "plt", "matplotlib")
    import_global(global_scope, "display", "idisplay", "IPython")
    import_global(global_scope, "typing")
    import_global(global_scope, "numpy", "np")

    import_global(global_scope, "librosa")
    import_global(global_scope, "soundfile")

    # Global variables.
    def import_and_print(name: str, value: typing.Any):
        global_scope[base_module].__dict__[name] = value
        print(name, "=", value)

    import_and_print(
        "IS_NOTEBOOK_KERNEL_CODE",
        value=is_notebook_kernel_code(global_scope),
    )
    import_and_print(
        "NOTEBOOK_NAME",
        value=get_notebook_name(global_scope),
    )
    import_and_print(
        "ASSETS_PATH",
        value=get_notebook_assets_path(global_scope),
    )

    # Progressively load up the directory tree.
    cur_path = global_scope[base_module].ASSETS_PATH
    while cur_path != os.path.dirname(cur_path):
        env_path = os.path.join(cur_path, ".env")
        if dotenv.load_dotenv(env_path):
            print(f"Loaded `{env_path}`.")
        cur_path = os.path.dirname(cur_path)
