import scrapy
import re
from urlparse import urlparse  
from scrapy.spiders import CrawlSpider, Rule
from scrapy.linkextractors import LinkExtractor
from ..items import Relationship 

class AmazonSpider(CrawlSpider):
    name = "amazon"
    allowed_domains = ["amazon.com", "aws.amazon.com"]
    start_urls = ["http://www.amazon.com/gp/pdp/profile/A3B32IOBMIOQ6C"]
    
    rules = (
        Rule(LinkExtractor(allow =('/gp/profile/products/'), restrict_xpaths= '//*[@class="a-column a-span8 title-container a-span-last"]/a[@href]'), callback= 'parse_review', follow=True),
        Rule(LinkExtractor(allow=('/gp/pdp/profile/',), restrict_xpaths= '////*[@id="revMHRL"]/div[*]/div/span/span[1]/a'), callback= 'parse_review', follow=True),
    )

    def __init__(self, *args, **kw):
        super(AmazonSpider, self).__init__()
        self.visited_users = set([])
    
    def parse_review(self,  response):
        if response.url.find("/gp/pdp/profile/") == -1:
            line = Relationship()
            temp = urlparse(response.url)
            temp = temp.path
            
            if '/dp/' in temp:
                line['e']= re.split('/dp/(\w+)', temp)[1]
            else: 
                line['e']= re.split('/gp/product/(\w+)', temp)[1]
                
            temp = urlparse(response.request.headers.get('Referer', None))
            temp = temp.path
            line['p'] = re.split('gp/pdp/profile/(\w+)',temp)[1]
            line['c'] = []
            
            page = response.xpath('//*[@id="revMHRL"]/div[*]/div/span/span[1]/a/@href').extract()
            #line['c'] = page
            
            for i in range(len(page)): 
                pos = re.split('/gp/pdp/profile/(\w+)', page[i])[1]
                line['c'].append(pos)
            
            if line['p'] not in self.visited_users:
                self.visited_users.add(line['p'])
                return line