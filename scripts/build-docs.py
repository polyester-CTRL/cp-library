"""Build dependency-free static HTML from repository documentation and headers."""
from html import escape
from pathlib import Path
root = Path(__file__).resolve().parents[1]
out = root / 'site'
out.mkdir(exist_ok=True)
files = [root / 'README.md', root / 'CONTRIBUTING.md']
files += sorted((root / 'docs').rglob('*.md'))
files += sorted((root / 'include/cp').rglob('*.hpp'))
sections = ''.join('<section><h2>' + escape(str(p.relative_to(root))) + '</h2><pre>'
                   + escape(p.read_text()) + '</pre></section>' for p in files)
(out / 'index.html').write_text('<!doctype html><html lang="en"><meta charset="utf-8">'
    '<meta name="viewport" content="width=device-width, initial-scale=1">'
    '<title>cp-library</title><style>body{max-width:70rem;margin:2rem auto;padding:1rem;'
    'font-family:system-ui}pre{white-space:pre-wrap;overflow-wrap:anywhere}</style>'
    '<h1>cp-library — C++17 / CC0-1.0</h1>' + sections + '</html>')
(out / '.nojekyll').touch()
print('Built site/index.html')
