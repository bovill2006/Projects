import pickle
import scrapy
import pdb
import re
from urlparse import urlparse  
from scrapy.spiders import CrawlSpider, Rule
from scrapy.linkextractors import LinkExtractor
from ..items import Relationship 

class AmazonSpider(CrawlSpider):
    name = "amazon"
    allowed_domains = ["amazon.com"]
    start_urls = ["http://www.amazon.com/gp/pdp/profile/A3PDQWY47JOVPT"]
    
    rules = (
        Rule(LinkExtractor(allow =('/gp/profile/products/'), restrict_xpaths= '//*[@class="a-column a-span8 title-container a-span-last"]/a[@href]'), callback= 'parse_review', follow=True),
        Rule(LinkExtractor(allow=('/gp/pdp/profile/',), restrict_xpaths= '//*[@id="revMHRL"]'), callback= 'parse_review', follow=True),
    )
    
    def make_requests_from_url(self, url):
        return scrapy.Request(url, dont_filter=True, meta = {
                'dont_redirect': True,
                'handle_httpstatus_list': [301,302]
            })
    
    def __init__(self, *args, **kw):
        super(AmazonSpider, self).__init__()
        self.visited_users = set([])
    
    def parse_review(self,  response):
        if response.url.find("/gp/pdp/profile/") == -1:
            line = Relationship()
            
            temp = urlparse(response.url)
            temp = temp.path
            line['e']= re.split('/dp/(\w+)', temp)[1]
            temp = urlparse(response.request.headers.get('Referer', None))
            temp = temp.path
            line['p'] = re.split('gp/pdp/profile/(\w+)',temp)[1]
            line['c'] = []#; pdb.set_trace()
            
            page = response.xpath('//*[@id="revMHRL"]/div[*]/div/span/span[1]/a/@href').extract()
            print page
            
            if page is not None: 
                for i in page: 
                    i = re.split('/gp/pdp/profile/(\w+)', i)[1]
                    line['c'].append(i)
            
            if line['p'] not in self.visited_users:
                self.visited_users.add(line['p'])
                return line