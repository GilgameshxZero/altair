import typing


# <https://stackoverflow.com/a/64791087>.
def import_global(
    global_scope: typing.Dict[str, str],
    object_name: str,
    short_name: str = "",
    context_module_name: str = "",
):
    """Use this statement to import inside a function,
    but effective as import at the top of the module."""
    if short_name == "":
        short_name = object_name
    if context_module_name == "":
        global_scope[short_name] = __import__(object_name)
    else:
        context_module = __import__(context_module_name, fromlist=[object_name])
        global_scope[short_name] = getattr(context_module, object_name)
    return global_scope[short_name]


def import_globals(global_scope: typing.Dict[str, str]):
    """Import commonly used globals under standard namespaces. Should pass `globals()` as the first argument.

    Typically, call at the top of the notebook."""
    from .filesystem import get_notebook_name, get_notebook_assets_path

    os = import_global(global_scope, "os")
    import_global(global_scope, "glob")
    import_global(global_scope, "pathlib")
    dotenv = import_global(global_scope, "dotenv")
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
    global_scope["NOTEBOOK_NAME"] = get_notebook_name(global_scope=global_scope)
    global_scope["ASSETS_PATH"] = get_notebook_assets_path(global_scope=global_scope)

    # Progressively load up the directory tree.
    cur_path = global_scope["ASSETS_PATH"]
    while cur_path != os.path.dirname(cur_path):
        env_path = os.path.join(cur_path, ".env")
        if dotenv.load_dotenv(env_path):
            print(f"Loaded `{env_path}`.")
        cur_path = os.path.dirname(cur_path)

    # Debug.
    print("ASSETS_PATH:", global_scope["ASSETS_PATH"])
