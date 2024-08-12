from __future__ import annotations
import abc
import enum
import json
import html.parser
import textwrap
import typing


class TextHTMLParser(html.parser.HTMLParser):
    class Element(abc.ABC):
        def __init__(self):
            self.elements = []

        def add_element(self, element):
            self.elements.append(element)

        @abc.abstractmethod
        def output(self, rend, level):
            raise RuntimeError('method not implemented')


    class EmptyElement(Element):
        def output(self, rend, level):
            yield from ()


    class RootElement(Element):
        def output(self, rend, level):
            for element in self.elements:
                yield element.output(rend, level)


    class Text(Element):
        def __init__(self, text):
            self.text = str(text)

        def add_element(self, element):
            raise RuntimeError('cannot add element to text')

        def output(self, rend, level):
            yield self.text


    class TextElement(Element):
        def wrap_text_escape(self, rend, width, indent=''):
            yield '\n'.join(self.wrap_text(rend, width, indent))

        def wrap_text(self, rend, width, indent=''):
            text = ''.join(e.output(rend, 0) for e in self.elements)
            yield from textwrap.wrap(text, 
                                     width=width, 
                                     initial_indent=indent)

        def wrap_text_mapped(self, mapper, rend, width, indent=''):
            yield '\n'.join(mapper(e) for e in self.wrap_text(rend, 
                                                              width, 
                                                              indent))


    class ParagraphElement(TextElement):
        def output(self, rend, level):
            tab = rend.tab(level)
            yield self.wrap_text_escape(rend, rend.max_width, tab)


    class ListElement(TextElement):
        def output(self, rend, level):
            offset = rend.list_mark_len
            yield self.wrap_text_escape(rend, rend.level_width(level, offset))


    class HeaderLargeElement(TextElement):
        def output(self, rend, level):
            offset = rend.header_large_len
            mark = rend.header_large_sym
            yield self.wrap_text_mapped(lambda line: '{} {} {}'.format(mark, 
                                                                       line,
                                                                       mark),
                                        rend, rend.level_width(level, offset))


    class HeaderSmallElement(TextElement):
        def output(self, rend, level):
            offset = rend.header_small_len
            mark = rend.header_small_sym
            yield self.wrap_text_mapped(lambda line: '{} {} {}'.format(mark, 
                                                                       line,
                                                                       mark),
                                        rend, rend.level_width(level, offset))


    class UnorderedElementList(Element):
        def output(self, rend, level):
            for element in self.elements:
                for number, line in enumerate(element.output(rend, level + 1)):
                    mark = rend.list_mark_sym if number == 0 else ''
                    tab = rend.tab(mark.rjust(rend.list_mark_len)) 
                    yield '{}{}'.format(tab, line)


    class OrderedElementList(Element):
        def output(self, rend, level):
            for element_number, element in enumerate(self.elements, start=1):
                for number, line in enumerate(element.output(rend, level + 1)):
                    mark = '{}.'.format(element_number) if number == 0 else ''
                    tab = rend.tab(mark.rjust(rend.list_mark_len)) 
                    yield '{}{}'.format(tab, line)


    class SectionElement(Element):
        def output(self, rend, level):
            for element in self.elements:
                yield element.output(rend, level + 1)
            yield ''
            yield rend.line(level + 1)
            yield ''


    class BreakElement(Element):
        def output(self, rend, level):
            yield '\n'


    class ItalicElement(Element):
        def output(self, rend, level):
            yield '_{}_'.format(0)


    class BoldElement(Element):
        def output(self, rend, level):
            yield '*{}*'.format(0)


    def __init__(self):
        super().__init__()
        
        self.root_element = TextHTMLParser.RootElement()
        self.element_stack = [self.root_element]
        self.element_map = {
            'p': TextHTMLParser.ParagraphElement,
            'h1': TextHTMLParser.HeaderLargeElement,
            'h2': TextHTMLParser.HeaderSmallElement,
            'h3': TextHTMLParser.HeaderSmallElement,
            'h4': TextHTMLParser.HeaderSmallElement,
            'h5': TextHTMLParser.HeaderSmallElement,
            'h6': TextHTMLParser.HeaderSmallElement,
            'ul': TextHTMLParser.UnorderedElementList,
            'ol': TextHTMLParser.OrderedElementList,
            'li': TextHTMLParser.ListElement,
            'br': TextHTMLParser.BreakElement,
            'i': TextHTMLParser.ItalicElement,
            'b': TextHTMLParser.BoldElement,
            'div': TextHTMLParser.SectionElement
        }

    def push_element(self, element):
        self.element_stack.append(element)

    @property
    def top_element(self):
        try:
            return self.element_stack[-1]
        except IndexError:
            return self.root_element

    def pop_element(self, element_class):
        if element_class is type(self.top_element):
            return self.element_stack.pop()
        return TextHTMLParser.EmptyElement()

    def handle_starttag(self, tag, attrs):
        try:
            element = self.element_map[tag]()
            self.top_element.add_element(element)
            self.push_element(element)
        except IndexError:
            pass
            
    def handle_endtag(self, tag):
        try:
            element_class = self.element_map[tag]
            self.pop_element(element_class)
        except IndexError:
            pass

    def handle_data(self, data):
        try:
            self.top_element.add_element(TextHTMLParser.Text(data))
        except AttributeError:
            pass

    def render(self, renderer):
        yield from self.root_element.output(renderer, 0)


class TextRenderer:
    def __init__(self, 
                 inset_width=2, 
                 max_width=80, 
                 list_mark_sym='<>', 
                 list_mark_len=4,
                 header_large_sym='==',
                 header_small_sym='--',
                 line_sym='-'):
        self.inset_width = inset_width
        self.max_width = max_width

        self.list_mark_sym = list_mark_sym
        self.list_mark_len = list_mark_len

        self.header_large_sym = header_large_sym
        self.header_large_len = len(header_large_sym) * 2 + 2

        self.header_small_sym = header_small_sym
        self.header_large_len = len(header_small_sym) * 2 + 2

        self.line_sym = line_sym

    def level_inset(self, level):
        return level * self.inset_width

    def level_width(self, level, offset=0):
        return self.max_width - self.level_inset(level) - offset

    def tab(self, level, after=''):
        return '{}{}'.format(' ' * self.level_inset(level), after)

    def line(self, level=0):
        return self.line_sym * self.level_width(level)


class ProjectReader:
    def __init__(self, jsonfile):
        self.jsonfile = jsonfile

    def print(self, rend):
        obj = json.load(self.jsonfile)

        title = obj.get('title', '<no title>')
        author = obj.get('author', '<unknown author>')
        time = obj.get('time', '<unknown time>')
        text_lines = obj.get('text', ['<p>blank</p>'])

        text = ''.join(text_lines)
        html_parser = TextHTMLParser()
        html_parser.feed(text)

        print('\n'.join(html_parser.render(rend)))
        print('\nmetadata:\n')
        print('  title = {}'.format(title))
        print('  author = {}'.format(author))
        print('  time = {}'.format(time))


class ConfigWriter:
    class AssignType(enum.Enum):
        EQ = '='
        ADD = '+='
        COND = '?='
        
    def __init__(self, makefile):
        self.makefile = makefile

    def set_row(self, name, value, assign_type=AssignType.EQ):
        row = '{} {} {}\n'.format(name, assign_type.value, value)
        self.makefile.write(row)

    def add_row(self, name, value):
        self.set_row(name, value, assign_type=ConfigWriter.AssignType.ADD)
    
    def add_row_list(self, name, values):
        for value in values:
            self.set_row(name, value, assign_type=ConfigWriter.AssignType.ADD)

    def set_row_if_empty(self, name, value):
        self.set_row(name, value, assign_type=ConfigWriter.AssignType.COND)


class Dialog:
    class OptionType:
        def __init__(self, default_value):
            self.default_value = default_value

        def skip(self):
            return self.default_value


    class IntOptionType(OptionType):
        def __init__(self, min_value, max_value, default_value):
            super().__init__(default_value)
            self.min_value = min_value
            self.max_value = max_value

        def parse(self, text):
            text = text.strip().lower()
            try:
                if text == '':
                    return self.default_value
                else:
                    return int(text)
            except ValueError:
                raise ValueError('invalid integer')

        def get_options_text(self):
            i = self.min_value
            j = self.max_value
            k = self.default_value
            return '{}, {}, ..., {} ({})'.format(i, i + 1, j, k)

        def is_valid(self, value):
            if value is None:
                return True
            return self.min_value <= value < self.max_value


    class TextOptionType(OptionType):
        def __init__(self, default_value):
            super().__init__(default_value)

        def parse(self, text):
            return text

        def get_options_text(self):
            return self.default_value

        def is_valid(self, _):
            return True


    class BoolOptionType(OptionType):
        def __init__(self, default_value):
            super().__init__(default_value)
        
        def parse(self, text):
            text = text.strip().lower()
            if text == '':
                return self.default_value
            if text in ['y', 'yes', '0']:
                return True
            if text in ['n', 'no', '1']:
                return False
            raise ValueError('not a boolean answer')

        def get_options_text(self):
            if self.default_value:
                return 'Y/n'
            else:
                return 'y/N'

        def is_valid(self, _):
            return True


    class CaseOptionType(OptionType):
        def __init__(self, cases, default_value):
            super().__init__(default_value)
            self.cases = cases

        def parse(self, text):
            text = text.strip().lower()
            if text == '':
                return self.default_value
            if text.isdigit():
                index = int(text)
                return self.cases[index]
            if text in self.cases:
                return text
            raise ValueError('not a one of options')

        def get_options_text(self):
            return '{} ({})'.format(', '.join(self.cases), self.default_value)

        def is_valid(self, value):
            return value in self.cases


    class Option:
        def __init__(self, name, text, option_type):
            self.name = name
            self.text = text
            self.option_type = option_type
            self.value = None
            self.on_value_set = lambda _: None

        def skip(self):
            self.value = self.option_type.skip()

        def prompt(self):
            options_text = self.option_type.get_options_text()
            body = '{} [{}] '.format(self.text, options_text)
            while True:
                response = input(body)
                try:
                    value = self.option_type.parse(response)
                    if self.option_type.is_valid(value):
                        self.value = value
                        self.on_value_set(value)
                        break
                    else:
                        print('invalid value specified')
                except ValueError as e:
                    print(e)

    def __init__(self):
        self.run_status = False
        self.skip_status = False
        self.options = []

    def add_option(self, name, text, option_type):
        if self.has_option(name):
            raise RuntimeError('option by name {} already exists'.format(name))
        self.options.append(Dialog.Option(name, text, option_type))

    def attach_on_entered(self, name, handler):
        self.get_option(name).on_value_set = handler

    def run(self):
        self.run_status = True
        self.skip_status = False

        try:
            for option in self.options:
                if self.skip_status:
                    break
                option.prompt()
        except EOFError:
            self.run_status = False

    def skip(self):
        self.skip_status = True

        for option in self.options:
            option.skip()

    def has_option(self, name):
        for option in self.options:
            if option.name == name:
                return True
        return False

    def get_option(self, name):
        for option in self.options:
            if option.name == name:
                return option
        raise RuntimeError('no such name {}'.format(name))

    def get_value(self, name):
        return self.get_option(name).value

    def get_items(self):
        for option in self.options:
            yield option.name, option.value


def map_bool(true_value, false_value, selector):
    return true_value if selector else false_value


text_rend = TextRenderer()

filename_out = 'makefile.in'

default_programmer = 'usbasp'

if __name__ == '__main__':
    with open('project.json', 'r', encoding='utf-8') as project_in:
        project = ProjectReader(project_in)
        project.print(text_rend)

    print('\nmakefile configurator')
    print('  output to: {}'.format(filename_out))
    print('  use <Ctrl-D> to cancel configuration')

    dialog = Dialog()

    def skip_handler(v):
        if v:
            dialog.skip()

    dialog.add_option(
            'skip',
            'reset to default?',
            Dialog.BoolOptionType(False)
    )
    dialog.attach_on_entered(
            'skip',
            skip_handler
    )
    dialog.add_option(
            'wextra',
            'enable extra warnings?',
            Dialog.BoolOptionType(False)
    )
    dialog.add_option(
            'stripmore',
            'strip as much as you can?',
            Dialog.BoolOptionType(True)
    )
    dialog.add_option(
            'opt',
            'select optimization level',
            Dialog.CaseOptionType(('0', '2', 's'), 's')
    )
    dialog.add_option(
            'prog',
            'choose programmer',
            Dialog.TextOptionType(default_programmer)
    )
    dialog.add_option(
            'baud',
            'override baud rate',
            Dialog.IntOptionType(300, 115_200, None)
    )

    
    dialog.run()

    if not dialog.run_status and not dialog.skip_status:
        print('---')
        print('exit configurator - no configuration saved')
        exit()

    if dialog.run_status and dialog.skip_status:
        print('using default values')

    with open(filename_out, 'w', encoding='ascii') as file_out:
        config = ConfigWriter(file_out)

        if dialog.get_value('wextra'):
            config.add_row('XCCF', '-Wextra')

        if dialog.get_value('stripmore'):
            config.add_row('ECCF', '-Wl,-static')
            config.add_row('ECCF', '-fdata-sections')
            config.add_row('ECCF', '-ffunction-sections')
            config.add_row('ECCF', '-Wl,-gc-sections')

        config.add_row('XCCF', '-O{}'.format(dialog.get_value('opt')))

        config.add_row('XADF', '-c {}'.format(dialog.get_value('prog')))
        if dialog.get_value('baud'):
            config.add_row('XADF', '-b {}'.format(dialog.get_value('baud')))

    print('done - saved to {}'.format(filename_out))

